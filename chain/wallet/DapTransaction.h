#ifndef DAPTRANSACTION_H
#define DAPTRANSACTION_H

#include <QObject>
#include "DapNetwork.h"
//#include "DatTokenValue.h"

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
public:
    Q_INVOKABLE explicit DapTransaction(QObject* a_parent = nullptr);
    Q_INVOKABLE explicit DapTransaction(DapNetwork* a_network,
                                        DapTransactionStatus a_status,
                                        size_t a_confirmationsCount,
                                        //DapTokenValue* a_tokenValue,
                                        QObject* a_parent = nullptr);

    Q_PROPERTY(DapNetwork*          network             READ network            WRITE setNetwork            NOTIFY networkChanged)
    Q_PROPERTY(DapTransactionStatus status              READ status             WRITE setStatus             NOTIFY statusChanged)
    Q_PROPERTY(size_t               confirmationsCount  READ confirmationsCount WRITE setConfirmationsCount NOTIFY confirmationsCountChanged)
    Q_PROPERTY(DapTokenValue*       tokenValue          READ tokenValue         WRITE setTokenValue         NOTIFY tokenValueChanged)

    Q_INVOKABLE DapNetwork* network()         { return m_network; }
    Q_INVOKABLE DapTransactionStatus status() { return m_status;  }
    Q_INVOKABLE size_t confirmationsCount()   { return m_confirmationsCount; }
    //Q_INVOKABLE DapTokenValue* tokenValue()   { return m_tokenValue; }

    Q_INVOKABLE void setNetwork(DapNetwork* a_network);
    Q_INVOKABLE void setStatus (DapTransactionStatus a_status);
    Q_INVOKABLE void setConfirmationsCount(size_t a_confirmationsCount);
    //Q_INVOKABLE void setTokenValue (DapTokenValue* a_tokenValue);

signals:
    void networkChanged(DapNetwork*);
    void statusChanged(DapTransactionStatus);
    void confirmationsCountChanged(size_t);
    //void tokenValueChanged(DapTokenValue*);

private:
    DapNetwork* m_network{Q_NULLPTR};
    DapTransactionStatus m_status{};
    size_t m_confirmationsCount{};
    //DapTokenValue* m_tokenValue{Q_NULLPTR};
};
Q_DECLARE_METATYPE(DapTransaction)
#endif // DAPTRANSACTION_H
