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

DapVpnOrder::DapVpnOrder(QObject *parent)
    : QObject(parent)
{
}

DapVpnOrder::DapVpnOrder(const DapVpnOrder &aOrder):
    m_name(aOrder.m_name),
    m_created(aOrder.m_created),
    m_units(aOrder.m_units),
    m_type(aOrder.m_type),
    m_tokenValue(aOrder.m_tokenValue)
{

}

DapVpnOrder &DapVpnOrder::operator=(const DapVpnOrder &aOrder)
{
    if (aOrder.m_name != m_name) {
        m_name = aOrder.m_name;
        m_created = aOrder.m_created;
        m_units = aOrder.m_units;
        m_type = aOrder.m_type;
        m_tokenValue = aOrder.m_tokenValue;
    }
    return (*this);
}

QString DapVpnOrder::name() const
{
    return m_name;
}

void DapVpnOrder::setName(const QString &a_name)
{
    if (a_name != m_name) {
        m_name = a_name;
        emit nameChanged(m_name);
    }
}

QDateTime DapVpnOrder::date() const
{
    return m_created;
}

void DapVpnOrder::setDate(const QDateTime &a_date)
{
    if (a_date != m_created) {
        m_created = a_date;
        emit dateChanged(m_created);
    }
}

int DapVpnOrder::units() const
{
    return m_units;
}

void DapVpnOrder::setUnits(int a_units)
{
    if (a_units != m_units) {
        m_units = a_units;
        emit unitsChanged(m_units);
    }
}

QString DapVpnOrder::type() const
{
    return s_types.takeAt(m_type);
}

void DapVpnOrder::setType(const QString &a_type)
{
    if (a_type != type())
        return;

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

void DapVpnOrder::setTokenValue(DapTokenValue *a_tokenValue)
{
    if (m_tokenValue == a_tokenValue) return;
    m_tokenValue = a_tokenValue;
    emit tokenValueChanged(a_tokenValue);
}

