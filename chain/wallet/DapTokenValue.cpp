#include "DapTokenValue.h"

#include <cmath>


DapTokenValue::DapTokenValue(const DapToken *a_token, balance_t a_amount, QObject* a_parent)
    : QObject   (a_parent)
    , m_token   (a_token)
    , m_amount  (a_amount)
{}

DapTokenValue::DapTokenValue(const DapTokenValue &a_token)
    : m_token   (a_token.m_token)
    , m_amount  (a_token.m_amount)
{}

DapTokenValue &DapTokenValue::operator=(const DapTokenValue &a_token)
{
    if(this != &a_token)
    {
        this->setToken(a_token.token());
        this->setAmount(a_token.amount());
    }
    return *this;
}

QString DapTokenValue::amountString() const
{
    return DapTokenValue::datoshiAmountToTokensString(m_amount);
}

void DapTokenValue::setToken(DapToken *a_token)
{
    if (a_token == m_token)
        return;

    m_token = a_token;
    emit this->tokenChanged(a_token);
    emit this->representationChanged(this->representation());
}

void DapTokenValue::setAmount(balance_t a_amount)
{
    if (m_amount == a_amount)
        return;

    m_amount = a_amount;
    emit this->amountChanged(a_amount);
    emit this->amountStringChanged(this->amountString());
    emit this->representationChanged(this->representation());
}

QString DapTokenValue::tokensAmountStringToDatoshiString(const QString &a_tokensString)
{
    return DapTokenValue::datoshiAmountToDatoshiString(DapTokenValue::tokensAmountStringToDatoshiAmount(a_tokensString));
}

QString DapTokenValue::datoshiAmountToTokensString(balance_t a_amount)
{
    unsigned long datoshiKoef = DATOSHI_KOEF;
    unsigned long tokenPart = a_amount / datoshiKoef;
    unsigned long datoshiPart = a_amount % datoshiKoef;

    auto resultString = QString("%1.%2").arg(tokenPart).arg(datoshiPart, DATOSHI_EXP, 10, QChar('0'));

    while (resultString.endsWith('0'))
    {
        resultString.chop(1);
    }

    if (resultString.endsWith(','))
        resultString.chop(1);

    return resultString;
}

QString DapTokenValue::datoshiAmountToDatoshiString(balance_t a_amount)
{
    unsigned long datoshiKoef = DATOSHI_KOEF;
    unsigned long tokenPart = a_amount / datoshiKoef;
    unsigned long datoshiPart = a_amount % datoshiKoef;

    QString string = QString::number(datoshiPart);

    if (tokenPart > 0)
        string = QString::number(tokenPart) + string;

    return string;
}

balance_t DapTokenValue::datoshiStringToTokensAmount(QString a_datoshiAmount)
{
    balance_t result = 0;

    while (a_datoshiAmount.count() > 1 && a_datoshiAmount.startsWith('0'))
    {
        a_datoshiAmount.remove(0, 1);
    }

    while (a_datoshiAmount.count() > 0) {
        result = result * 10 + QString(a_datoshiAmount.at(0)).toInt();
        a_datoshiAmount.remove(0, 1);
    }
    return result;
}

balance_t DapTokenValue::tokensAmountStringToDatoshiAmount(const QString& a_tokensAmount)
{
    auto strings = a_tokensAmount.split(QRegExp("[\\.,]"));

    auto& fractPartStr = strings.last();

    fractPartStr.append(QString(DATOSHI_EXP - fractPartStr.count(), '0'));

    return datoshiStringToTokensAmount(strings.first() + fractPartStr);
}

QString DapTokenValue::representation() const
{
    return this->amountString() + " " + m_token->name();
}

