#include "DapTransaction.h"

DapTransaction::DapTransaction(QObject *a_parent)
    : QObject(a_parent)
{
}

DapTransaction::DapTransaction(DapNetwork* a_network,
                               DapTransactionStatus a_status,
                               size_t a_confirmationsCount,
                               DapTokenValue* a_tokenValue,
                               QObject* a_parent)
    : QObject               (a_parent)
    , m_network             (a_network)
    , m_status              (a_status)
    , m_confirmationsCount  (a_confirmationsCount)
    , m_tokenValue          (a_tokenValue)
{
}

DapTransaction::DapTransaction(const DapTransaction &a_transaction)
    : m_network             (a_transaction.m_network)
    , m_status              (a_transaction.m_status)
    , m_confirmationsCount  (a_transaction.m_confirmationsCount)
    , m_tokenValue          (a_transaction.m_tokenValue)
{
}

DapTransaction &DapTransaction::operator=(const DapTransaction &a_transaction)
{
    if(this != &a_transaction)
    {
        this->setNetwork(a_transaction.m_network);
        this->setStatus(a_transaction.m_status);
        this->setConfirmationsCount(a_transaction.m_confirmationsCount);
        this->setTokenValue(a_transaction.m_tokenValue);
    }
    return *this;
}

void DapTransaction::setNetwork(DapNetwork *a_network)
{
    if (a_network == m_network) return;
    m_network = a_network;
    emit networkChanged(a_network);
}

void DapTransaction::setStatus(DapTransactionStatus a_status)
{
    if (a_status == m_status) return;
    m_status = a_status;
    emit statusChanged(a_status);
}

void DapTransaction::setConfirmationsCount(size_t a_confirmationsCount)
{
    if (a_confirmationsCount == m_confirmationsCount) return;
    m_confirmationsCount = a_confirmationsCount;
    emit confirmationsCountChanged(a_confirmationsCount);
}

void DapTransaction::setTokenValue(DapTokenValue* a_tokenValue)
{
    if (a_tokenValue == m_tokenValue) return;
    m_tokenValue = a_tokenValue;
    emit tokenValueChanged(a_tokenValue);
}
