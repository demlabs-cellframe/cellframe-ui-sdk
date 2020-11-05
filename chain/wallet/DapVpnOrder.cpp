#include "DapVpnOrder.h"

QStringList DapVpnOrder::s_types = {
    QString("Unknown"),
    QString("Bytes"),
    QString("Megabytes"),
    QString("Gigabytes"),
    QString("Seconds"),
    QString("Minutes"),
    QString("Hours"),
    QString("Days"),
    QString("Month")
};

DapVpnOrder::DapVpnOrder(QObject *parent): QObject(parent)
{

}

DapVpnOrder::DapVpnOrder(const DapVpnOrder &aOrder):
    m_name(aOrder.m_name),
    m_created(aOrder.m_created),
    m_units(aOrder.m_units),
    m_type(aOrder.m_type),
    m_value(aOrder.m_value),
    m_tokenName(aOrder.m_tokenName)
{

}

DapVpnOrder &DapVpnOrder::operator=(const DapVpnOrder &aOrder)
{
    if (aOrder.m_name != m_name) {
        m_name = aOrder.m_name;
        m_created = aOrder.m_created;
        m_units = aOrder.m_units;
        m_type = aOrder.m_type;
        m_value = aOrder.m_value;
        m_tokenName = aOrder.m_tokenName;
    }
    return (*this);
}

QString DapVpnOrder::name() const
{
    return m_name;
}

void DapVpnOrder::setName(const QString &a_name)
{
    m_name = a_name;
    emit nameChanged(m_name);
}

QDateTime DapVpnOrder::date() const
{
    return m_created;
}

void DapVpnOrder::setDate(const QDateTime &a_date)
{
    m_created = a_date;
    emit dateChanged(m_created);
}

int DapVpnOrder::units() const
{
    return m_units;
}

void DapVpnOrder::setUnits(int a_units)
{
    m_units = a_units;
    emit unitsChanged(m_units);
}

QString DapVpnOrder::type() const
{
    return s_types.takeAt(m_type);
}

void DapVpnOrder::setType(const QString &a_type)
{
    int i = 0;
    for (auto str : s_types) {
        if (str == a_type) {
            m_type = DapVpnOrder::UnitType(i);
            emit typeChanged(type());
            break;
        }
        ++i;
    }
}

double DapVpnOrder::value() const
{
    return m_value;
}

void DapVpnOrder::setValue(double a_value)
{
    m_value = a_value;
    emit valueChanged(m_value);
}

QString DapVpnOrder::token() const
{
    return m_tokenName;
}

void DapVpnOrder::setToken(const QString &a_token)
{
    m_tokenName = a_token;
    emit tokenChanged(m_tokenName);
}

