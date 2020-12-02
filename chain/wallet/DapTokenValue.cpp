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
    return DapTokenValue::datoshiAmountToString(m_amount);
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

QString DapTokenValue::datoshiAmountToString(balance_t a_amount)
{
    unsigned int datoshiKoef = DATOSHI_KOEF;
    unsigned int tokenPart = a_amount / datoshiKoef;
    unsigned int datoshiPart = a_amount % datoshiKoef;

    auto resultString = QString("%1,%2").arg(tokenPart).arg(datoshiPart, DATOSHI_EXP, 10, QChar('0'));

    while (resultString.endsWith('0'))
    {
        resultString.chop(1);
    }

    return resultString;
}

balance_t DapTokenValue::datoshiStringtoTokensAmount(QString a_datoshiAmount)
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

balance_t DapTokenValue::tokensAmountStringtoTokensAmount(const QString& a_tokensAmount)
{
    auto strings = a_tokensAmount.split(QRegExp("[\\.,]"));

    auto& fractPartStr = strings.last();

    fractPartStr.append(QString(DATOSHI_EXP - fractPartStr.count(), '0'));

    return datoshiStringtoTokensAmount(strings.first() + fractPartStr);
}

QString DapTokenValue::representation() const
{
    return this->amountString() + " " + m_token->name();
}
