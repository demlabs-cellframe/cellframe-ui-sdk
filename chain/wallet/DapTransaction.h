#ifndef DAPTRANSACTION_H
#define DAPTRANSACTION_H

#include <QObject>
#include "DapNetwork.h"
#include "DapTokenValue.h"
#include <QDate>

class DapTransaction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const DapNetwork*    network             READ network            WRITE setNetwork            NOTIFY networkChanged)
    Q_PROPERTY(Status               status              READ status             WRITE setStatus             NOTIFY statusChanged)
    Q_PROPERTY(size_t               confirmationsCount  READ confirmationsCount WRITE setConfirmationsCount NOTIFY confirmationsCountChanged)
    Q_PROPERTY(DapTokenValue*       tokenValue          READ tokenValue         CONSTANT)
    Q_PROPERTY(QDate                date                READ date               WRITE setDate               NOTIFY dateChanged)


public:

    enum Status
    {
        Local,
        Mempool,
        Successful,
        Canceled
    }; Q_ENUM(Status)

    explicit DapTransaction(QObject* a_parent = nullptr);
    explicit DapTransaction(const DapNetwork *a_network,
                            Status a_status,
                            size_t a_confirmationsCount,
                            const DapTokenValue& a_tokenValue,
                            QDate a_date,
                            QObject* a_parent = nullptr);

    DapTransaction(const DapTransaction& a_transaction);
    DapTransaction &operator=(const DapTransaction& a_transaction);

    const DapNetwork* network()   const { return m_network;            }
    Status status()               const { return m_status;             }
    size_t confirmationsCount()   const { return m_confirmationsCount; }
    DapTokenValue* tokenValue()         { return &m_tokenValue;        }
    QDate date()                  const { return m_date;               }

    void setNetwork(const DapNetwork* a_network);
    void setStatus (Status a_status);
    void setConfirmationsCount(size_t a_confirmationsCount);
    void setTokenValue (const DapTokenValue &a_tokenValue);
    void setDate(QDate a_date);

signals:
    void networkChanged(const DapNetwork*);
    void statusChanged(Status);
    void confirmationsCountChanged(size_t);
    void dateChanged(QDate);

private:
    const DapNetwork*    m_network = nullptr;
    Status               m_status{};
    size_t               m_confirmationsCount{};
    DapTokenValue        m_tokenValue;
    QDate                m_date{};
};
#endif // DAPTRANSACTION_H
