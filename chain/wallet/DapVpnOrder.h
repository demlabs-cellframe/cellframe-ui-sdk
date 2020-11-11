#ifndef DAPVPNORDER_H
#define DAPVPNORDER_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include "DapToken.h"
#include "DapTokenValue.h"

class DapVpnOrder : public QObject
{
    Q_OBJECT
public:
    enum UnitType {
        Unknown,
        Bytes,
        Megabytes,
        Gigabytes,
        Seconds,
        Minutes,
        Hours,
        Days,
        Month
    };
    Q_ENUM(UnitType)

    Q_INVOKABLE explicit DapVpnOrder(QObject *parent = nullptr);
    Q_INVOKABLE DapVpnOrder(const DapVpnOrder& aOrder);
    Q_INVOKABLE DapVpnOrder& operator=(const DapVpnOrder& aOrder);

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(int units READ units WRITE setUnits NOTIFY unitsChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(DapTokenValue* tokenValue READ tokenValue CONSTANT)

    QString name() const;
    void setName(const QString &a_name);
    QDateTime date() const;
    void setDate(const QDateTime &a_date);
    int units() const;
    void setUnits(int a_units);
    QString type() const;
    void setType(const QString &a_type);
    balance_t amount() const            { return m_tokenValue.amount();     }
    DapToken* token()  const            { return m_tokenValue.token();      }
    DapTokenValue* tokenValue()         { return &m_tokenValue;             }
    void setAmount(balance_t a_amount)  { m_tokenValue.setAmount(a_amount); }
    void setToken(DapToken* a_token)    { m_tokenValue.setToken(a_token);   }

signals:
    void nameChanged(const QString& a_name);
    void dateChanged(const QDateTime& a_date);
    void unitsChanged(int a_units);
    void typeChanged(const QString& a_type);

private:
    static QStringList s_types;
    QString   m_name;
    QDateTime m_created;
    int       m_units = 0;
    UnitType  m_type = UnitType::Unknown;
    DapTokenValue m_tokenValue{};
};
Q_DECLARE_METATYPE(DapVpnOrder)

#endif // DAPVPNORDER_H
