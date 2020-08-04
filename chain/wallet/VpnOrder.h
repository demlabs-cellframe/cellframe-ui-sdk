#ifndef VPNORDER_H
#define VPNORDER_H

#include <QObject>

class VpnOrder : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(bool switchedOn READ getSwitchedOn WRITE setSwitchedOn NOTIFY switchedOnChanged)

    enum UnitsType
    {
        Seconds = 0,
        Minutes,
        Hours,
        Days,
        Kilobyte,
        Megabyte,
        Gigabyte
    };
    Q_ENUM(UnitsType);

    VpnOrder(QObject *parent = nullptr);

    VpnOrder (const VpnOrder &order);

    VpnOrder(QString name, QString region, int units,
             UnitsType unitsType, double value, QString token,
             bool unsafe = false, int speedLimit = -1, QObject *parent = nullptr);

    VpnOrder& operator=(const VpnOrder& order);

    QString     getName()       const;
    QString     getRegion()     const;
    bool        getSwitchedOn() const;
    int         getUnits()      const;
    UnitsType   getUnitsType()  const;
    double      getValue()      const;
    QString     getToken()      const;
    bool        getUnsafe()     const;
    int         getSpeedLimit() const;

    void setName(QString value);
    void setRegion(QString value);
    void setSwitchedOn(bool value);
    void setUnits(int value);
    void setUnitsType(UnitsType value);
    void setValue(double value);
    void setToken(QString value);
    void setUnsafe(bool value);
    void setSpeedLimit(int value);

private:
    QString     m_name;
    QString     m_region;
    bool        m_switchedOn;
    int         m_units;
    UnitsType   m_unitsType;
    double      m_value;
    QString     m_token;
    bool        m_unsafe;
    int         m_speedLimit;

signals:
    void switchedOnChanged(const bool& value);
};

#endif // VPNORDER_H
