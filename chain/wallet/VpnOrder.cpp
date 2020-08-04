#include "VpnOrder.h"

VpnOrder::VpnOrder(QObject *parent) : QObject(parent)
{

}

VpnOrder::VpnOrder(const VpnOrder &order)
{
    this->setParent(order.parent());
    setName(order.getName());
    setRegion(order.getRegion());
    setSwitchedOn(order.getSwitchedOn());
    setUnits(order.getUnits());
    setUnitsType(order.getUnitsType());
    setValue(order.getValue());
    setToken(order.getToken());
    setUnsafe(order.getUnsafe());
    setSpeedLimit(order.getSpeedLimit());
}

VpnOrder::VpnOrder(QString name, QString region, int units,
                   UnitsType unitsType, double value, QString token,
                   bool unsafe, int speedLimit, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_region(region)
    , m_switchedOn(false)
    , m_units(units)
    , m_unitsType(unitsType)
    , m_value(value)
    , m_token(token)
    , m_unsafe(unsafe)
    , m_speedLimit(speedLimit)
{

}

VpnOrder &VpnOrder::operator=(const VpnOrder &order)
{
    this->setParent(order.parent());
    setName(order.getName());
    setRegion(order.getRegion());
    setSwitchedOn(order.getSwitchedOn());
    setUnits(order.getUnits());
    setUnitsType(order.getUnitsType());
    setValue(order.getValue());
    setToken(order.getToken());
    setUnsafe(order.getUnsafe());
    setSpeedLimit(order.getSpeedLimit());
    return *this;
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

VpnOrder::UnitsType VpnOrder::getUnitsType() const
{
    return m_unitsType;
}

double VpnOrder::getValue() const
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

void VpnOrder::setName(QString value)
{
    m_name = value;
}

void VpnOrder::setRegion(QString value)
{
    m_region = value;
}

void VpnOrder::setSwitchedOn(bool value)
{
    m_switchedOn = value;

    emit switchedOnChanged(value);
}

void VpnOrder::setUnits(int value)
{
    m_units = value;
}

void VpnOrder::setUnitsType(UnitsType value)
{
    m_unitsType = value;
}

void VpnOrder::setValue(double value)
{
    m_value = value;
}

void VpnOrder::setToken(QString value)
{
    m_token = value;
}

void VpnOrder::setUnsafe(bool value)
{
    m_unsafe = value;
}

void VpnOrder::setSpeedLimit(int value)
{
    m_speedLimit = value;
}


