#ifndef DAPTRANSACTION_H
#define DAPTRANSACTION_H

#include <QObject>
#include "DapNetwork.h"
#include "DapTokenValue.h"

enum DapTransactionStatus
{
    Local,
    Mempool,
    Successful,
    Canceled
};

class DapTransaction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DapNetwork*          network             READ network            WRITE setNetwork            NOTIFY networkChanged)
    Q_PROPERTY(DapTransactionStatus status              READ status             WRITE setStatus             NOTIFY statusChanged)
    Q_PROPERTY(size_t               confirmationsCount  READ confirmationsCount WRITE setConfirmationsCount NOTIFY confirmationsCountChanged)
    Q_PROPERTY(DapTokenValue*       tokenValue          READ tokenValue         CONSTANT)


public:
    explicit DapTransaction(QObject* a_parent = nullptr);
    explicit DapTransaction(DapNetwork* a_network,
                            DapTransactionStatus a_status,
                            size_t a_confirmationsCount,
                            DapTokenValue* a_tokenValue,
                            QObject* a_parent = nullptr);

    DapTransaction(const DapTransaction& a_transaction);
    DapTransaction &operator=(const DapTransaction& a_transaction);

    DapNetwork* network()         const { return m_network;            }
    DapTransactionStatus status() const { return m_status;             }
    size_t confirmationsCount()   const { return m_confirmationsCount; }
    DapTokenValue* tokenValue()         { return &m_tokenValue;        }

    void setNetwork(const DapNetwork* a_network);
    void setStatus (DapTransactionStatus a_status);
    void setConfirmationsCount(size_t a_confirmationsCount);
    void setTokenValue (const DapTokenValue &a_tokenValue);

signals:
    void networkChanged(DapNetwork*);
    void statusChanged(DapTransactionStatus);
    void confirmationsCountChanged(size_t);

private:
    DapNetwork*          m_network = nullptr;
    DapTransactionStatus m_status{};
    size_t               m_confirmationsCount{};
    DapTokenValue        m_tokenValue;
};
#endif // DAPTRANSACTION_H
