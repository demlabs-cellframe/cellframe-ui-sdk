#ifndef DAPTRANSACTION_H
#define DAPTRANSACTION_H

#include <QObject>
#include "DapNetwork.h"
#include "DapTokenValue.h"
#include <QDateTime>

class DapTransaction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DapNetwork*          network             READ network            WRITE setNetwork            NOTIFY networkChanged)
    Q_PROPERTY(Status               status              READ status             WRITE setStatus             NOTIFY statusChanged)
    Q_PROPERTY(size_t               confirmationsCount  READ confirmationsCount WRITE setConfirmationsCount NOTIFY confirmationsCountChanged)
    Q_PROPERTY(DapTokenValue*       tokenValue          READ tokenValue         CONSTANT)
    Q_PROPERTY(QDateTime            date                READ date               WRITE setDate               NOTIFY dateChanged)
    Q_PROPERTY(QString              sumRepresentation   READ sumRepresentation                              NOTIFY sumRepresentationChanged)

public:

    enum Type
    {
        EXPENSE,
        INCOME
    };

    enum Status
    {
        LOCAL,
        MEMPOOL,
        SUCCESSFUL,
        CANCELED
    }; Q_ENUM(Status)

    explicit DapTransaction(QObject* a_parent = nullptr);

    DapTransaction(const DapTransaction& a_transaction);
    DapTransaction &operator=(const DapTransaction& a_transaction);

    DapNetwork* network()         const { return m_network;            }
    Status status()               const { return m_status;             }
    size_t confirmationsCount()   const { return m_confirmationsCount; }
    const DapTokenValue* tokenValue()   const { return &m_tokenValue;        }
    DapTokenValue* tokenValue()         { return &m_tokenValue;        }
    QDateTime date()              const { return m_date;               }
    QString  hash()               const { return m_hash;               }
    QString sumRepresentation() const;

    void setNetwork(DapNetwork* a_network);
    void setStatus (Status a_status);
    void setConfirmationsCount(size_t a_confirmationsCount);
    void setTokenValue (const DapTokenValue &a_tokenValue);
    void setDate(QDateTime a_date);
    void setHash(QString a_hash);
    void setType(Type a_type);

    Q_INVOKABLE QString statusRepresentation() const;

signals:
    void networkChanged(DapNetwork*);
    void statusChanged(Status);
    void confirmationsCountChanged(size_t);
    void dateChanged(QDateTime);
    void sumRepresentationChanged(QString);

private:
    DapNetwork*          m_network = nullptr;
    Status               m_status{};
    size_t               m_confirmationsCount{};
    DapTokenValue        m_tokenValue;
    QDateTime            m_date{};
    QString              m_hash;

    Type m_type;
};
#endif // DAPTRANSACTION_H
