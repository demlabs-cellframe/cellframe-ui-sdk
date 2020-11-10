#include "DapTokenValue.h"

DapTokenValue::DapTokenValue(DapToken* a_token, balance_t a_amount, QObject* a_parent)
    : QObject   (a_parent)
    , m_token   (a_token)
    , m_amount  (a_amount) {}

DapTokenValue::DapTokenValue(const DapTokenValue &a_token)
    : m_token   (a_token.m_token)
    , m_amount  (a_token.m_amount) {}

DapTokenValue &DapTokenValue::operator=(const DapTokenValue &a_token)
{
    if(this != &a_token)
    {
        m_token = a_token.m_token;
        m_amount = a_token.m_amount;
    }
    return *this;
}

void DapTokenValue::setToken(DapToken *a_token)
{
    if (a_token == m_token) return;
    m_token = a_token;
    emit tokenChanged(a_token);
}

void DapTokenValue::setAmount(balance_t a_amount)
{
    if (m_amount == a_amount) return;
    m_amount = a_amount;
    emit amountChanged(a_amount);
}
