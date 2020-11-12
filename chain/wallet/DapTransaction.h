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
    Q_PROPERTY(DapTokenValue*       tokenValue          READ tokenValue         WRITE setTokenValue         NOTIFY tokenValueChanged)

public:
    explicit DapTransaction(QObject* a_parent = nullptr);
    explicit DapTransaction(DapNetwork* a_network,
                                        DapTransactionStatus a_status,
                                        size_t a_confirmationsCount,
                                        DapTokenValue* a_tokenValue,
                                        QObject* a_parent = nullptr);
    DapTransaction(const DapTransaction& a_transaction);
    DapTransaction &operator=(const DapTransaction& a_transaction);

    DapNetwork* network()         { return m_network;            }
    DapTransactionStatus status() { return m_status;             }
    size_t confirmationsCount()   { return m_confirmationsCount; }
    DapTokenValue* tokenValue()   { return m_tokenValue;         }

    void setNetwork(DapNetwork* a_network);
    void setStatus (DapTransactionStatus a_status);
    void setConfirmationsCount(size_t a_confirmationsCount);
    void setTokenValue (DapTokenValue* a_tokenValue);

signals:
    void networkChanged(DapNetwork*);
    void statusChanged(DapTransactionStatus);
    void confirmationsCountChanged(size_t);
    void tokenValueChanged(DapTokenValue*);

private:
    DapNetwork*          m_network = nullptr;
    DapTransactionStatus m_status{};
    size_t               m_confirmationsCount{};
    DapTokenValue*       m_tokenValue = nullptr;
};
Q_DECLARE_METATYPE(DapTransaction)
#endif // DAPTRANSACTION_H
