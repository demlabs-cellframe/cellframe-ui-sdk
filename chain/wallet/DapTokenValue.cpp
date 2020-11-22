#include "DapTokenValue.h"

DapTokenValue::DapTokenValue(DapToken* a_token, balance_t a_amount, QObject* a_parent)
    : QObject   (a_parent)
    , m_token   (a_token)
    , m_amount  (a_amount)
    , m_sign    (Sign::NONE)
{}
DapTokenValue::DapTokenValue(DapToken* a_token, balance_t a_amount, Sign a_sign, QObject *a_parent)
    : QObject   (a_parent)
    , m_token   (a_token)
    , m_amount  (a_amount)
    , m_sign    (a_sign)
{}

DapTokenValue::DapTokenValue(const DapTokenValue &a_token)
    : m_token   (a_token.m_token)
    , m_amount  (a_token.m_amount)
    , m_sign     (a_token.m_sign)
{}

DapTokenValue &DapTokenValue::operator=(const DapTokenValue &a_token)
{
    if(this != &a_token)
    {
        this->setToken(a_token.m_token);
        this->setAmount(a_token.m_amount);
        this->setSign(a_token.m_sign);
    }
    return *this;
}

void DapTokenValue::setToken(DapToken *a_token)
{
    if (a_token == m_token)
        return;

    m_token = a_token;
    emit tokenChanged(a_token);
}

void DapTokenValue::setAmount(balance_t a_amount)
{
    if (m_amount == a_amount)
        return;

    m_amount = a_amount;
    emit amountChanged(a_amount);
}

QString DapTokenValue::representation() const
{
    QString sign;
    if(m_sign == Sign::NONE)
        sign = "";
    else if(m_sign == Sign::PLUS)
            sign = "+";
    else
            sign = "-";

    return sign + QString::number(m_amount) + " " + m_token->name();
}

void DapTokenValue::setSign(Sign a_sign)
{
    if( m_sign == a_sign )
        return;

        m_sign = a_sign;
        emit signChanged(m_sign);
}
