#include "DapTokenValue.h"

DapTokenValue::DapTokenValue(DapToken* a_token, balance_t a_amount, QObject* a_parent)
    : QObject   (a_parent)
    , m_token   (a_token)
    , m_amount  (a_amount)
{

}

void DapTokenValue::setToken(DapToken *a_token)
{
    if (a_token != m_token)
    {
        m_token = a_token;
        emit tokenChanged(a_token);
    }
    else return;
}

void DapTokenValue::setAmount(balance_t a_amount)
{
    if (m_amount != a_amount)
    {
        m_amount = a_amount;
        emit amountChanged(a_amount);
    }
    else return;
}
