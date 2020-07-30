#ifndef VPNORDER_H
#define VPNORDER_H

#include <QObject>

class VpnOrder
{
    QString     m_name;
    QString     m_region;
    bool        m_switchedOn;
    int         m_units;
    QString     m_unitsType;
    double      m_value;
    QString     m_token;
    bool        m_unsafe;
    int         m_speedLimit;
public:
    VpnOrder(QString name, QString region, bool switchedOn,
             int units, QString unitsType, double value,
             QString token, bool unsafe, int speedLimit);
    QString getName() const;
    QString getRegion() const;
    bool getSwitchedOn() const;
    int getUnits() const;
    QString getUnitsType() const;
    int getValue() const;
    QString getToken() const;
    bool getUnsafe() const;
    int getSpeedLimit() const;
};

#endif // VPNORDER_H
