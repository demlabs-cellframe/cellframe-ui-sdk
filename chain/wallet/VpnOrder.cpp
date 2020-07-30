#include "VpnOrder.h"

VpnOrder::VpnOrder(QString name, QString region, bool switchedOn,
                   int units, QString unitsType, double value,
                   QString token, bool unsafe, int speedLimit)
    : m_name(name)
    , m_region(region)
    , m_switchedOn(switchedOn)
    , m_units(units)
    , m_unitsType(unitsType)
    , m_value(value)
    , m_token(token)
    , m_unsafe(unsafe)
    , m_speedLimit(speedLimit)
{

}

QString VpnOrder::getName() const
{
    return m_name;
}

QString VpnOrder::getRegion() const
{
    return m_region;
}

bool VpnOrder::getSwitchedOn() const
{
    return m_switchedOn;
}

int VpnOrder::getUnits() const
{
    return m_units;
}

QString VpnOrder::getUnitsType() const
{
    return m_unitsType;
}

int VpnOrder::getValue() const
{
    return m_value;
}

QString VpnOrder::getToken() const
{
    return m_token;
}

bool VpnOrder::getUnsafe() const
{
    return m_unsafe;
}

int VpnOrder::getSpeedLimit() const
{
    return m_speedLimit;
}


