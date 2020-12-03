#include "DapTransaction.h"

DapTransaction::DapTransaction(QObject *a_parent)
    : QObject(a_parent)
{
    connect(&m_tokenValue, &DapTokenValue::representationChanged, [this]{
        emit this->sumRepresentationChanged(this->sumRepresentation());
    });
}

DapTransaction::DapTransaction(const DapTransaction &a_transaction)
    : m_network             (a_transaction.m_network)
    , m_status              (a_transaction.m_status)
    , m_confirmationsCount  (a_transaction.m_confirmationsCount)
    , m_tokenValue          (a_transaction.m_tokenValue)
    , m_date                (a_transaction.m_date)
    , m_hash                (a_transaction.m_hash)
{
}

DapTransaction &DapTransaction::operator=(const DapTransaction &a_transaction)
{
    if(this != &a_transaction)
    {
        this->setNetwork(a_transaction.m_network);
        this->setStatus(a_transaction.m_status);
        this->setConfirmationsCount(a_transaction.m_confirmationsCount);
        this->setTokenValue(const_cast<DapTokenValue&>(a_transaction.m_tokenValue));
        this->setDate(a_transaction.m_date);
    }
    return *this;
}

QString DapTransaction::sumRepresentation() const
{
    return m_type == Type::EXPENSE ? "-" : "" + this->tokenValue()->representation();
}

void DapTransaction::setNetwork(DapNetwork *a_network)
{
    if (a_network == m_network)
        return;
    m_network = a_network;
    emit networkChanged(m_network);
}

void DapTransaction::setStatus(Status a_status)
{
    if (a_status == m_status)
        return;
    m_status = a_status;
    emit statusChanged(a_status);
}

void DapTransaction::setConfirmationsCount(size_t a_confirmationsCount)
{
    if (a_confirmationsCount == m_confirmationsCount)
        return;
    m_confirmationsCount = a_confirmationsCount;
    emit confirmationsCountChanged(a_confirmationsCount);
}

void DapTransaction::setTokenValue(const DapTokenValue &a_tokenValue)
{
    if (&m_tokenValue == &a_tokenValue)
        return;
    m_tokenValue = a_tokenValue;
}

void DapTransaction::setDate(QDateTime a_date)
{
    if (a_date == m_date)
        return;
    m_date = a_date;
    emit dateChanged(a_date);
}

void DapTransaction::setHash(QString a_hash)
{
    m_hash = a_hash;
}

QString DapTransaction::statusRepresentation() const
{
    QString returnStr{};
    switch (this->status())
    {
    case Local:      returnStr = tr("Local");      break;
    case Mempool:    returnStr = tr("Mempool");    break;
    case Successful: returnStr = tr("Successful"); break;
    case Canceled:   returnStr = tr("Canceled");   break;
    }
    if(this->confirmationsCount() > 0)
        returnStr += " (" + QString::number(this->confirmationsCount()) + tr(" Confirms)");
    return returnStr;
}
