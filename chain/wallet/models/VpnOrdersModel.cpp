#include "VpnOrdersModel.h"

VpnOrdersModel* VpnOrdersModel::m_instance = nullptr;

VpnOrdersModel::VpnOrdersModel(QObject *parent)
    : QAbstractListModel(parent)
{
    VpnOrder order1("Auto server",  "Europe",       567,    VpnOrder::Seconds,  63,         "LSDO", false,  1);
    VpnOrder order2("Auto Asia",    "England",      3600,   VpnOrder::Hours,    0.1,        "LFDF", false,  -1);
    VpnOrder order3("Auto Europe",  "Asia",         1230,   VpnOrder::Minutes,  48,         "ASAD", true,   1);
    VpnOrder order4("Auto USA",     "Germany",      854,    VpnOrder::Hours,    135.688,    "APSF", true,   -1);
    VpnOrder order5("Auto server",  "Auto",         6532,   VpnOrder::Seconds,  891.5,      "POAS", false,  1);
    VpnOrder order6("Auto server",  "Russian",      3521,   VpnOrder::Minutes,  79,         "CSDC", true,   1);
    VpnOrder order7("Auto server",  "Kazakhstan",   655,    VpnOrder::Seconds,  123.56,     "AFSG", false,  -1);
    VpnOrder order8("Auto server",  "USA",          186,    VpnOrder::Minutes,  0.56,       "AWER", true,   1);
    VpnOrder order9("Auto server",  "Canada",       10,     VpnOrder::Hours,    1.153,      "NDGF", false,  -1);

    order1.setSwitchedOn(true);
    order2.setSwitchedOn(true);
    order4.setSwitchedOn(true);
    order5.setSwitchedOn(true);
    order7.setSwitchedOn(true);

    m_vpnOrders.append(order1);
    m_vpnOrders.append(order2);
    m_vpnOrders.append(order3);
    m_vpnOrders.append(order4);
    m_vpnOrders.append(order5);
    m_vpnOrders.append(order6);
    m_vpnOrders.append(order7);
    m_vpnOrders.append(order8);
    m_vpnOrders.append(order9);
}

VpnOrdersModel *VpnOrdersModel::getInstance()
{
    if (m_instance == nullptr)
        m_instance = new VpnOrdersModel;

    return m_instance;
}

int VpnOrdersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_vpnOrders.count();
}

QVariant VpnOrdersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case nameDisplayRole:           return m_vpnOrders.at(index.row()).getName();
    case regionDisplayRole:         return m_vpnOrders.at(index.row()).getToken();
    case switchedOnDisplayRole:     return m_vpnOrders.at(index.row()).getSwitchedOn();
    case unitsDisplayRole:          return m_vpnOrders.at(index.row()).getUnits();
    case unitsTypeDisplayRole:      return m_vpnOrders.at(index.row()).getUnitsType();
    case valueDisplayRole:          return m_vpnOrders.at(index.row()).getValue();
    case tokenDisplayRole:          return m_vpnOrders.at(index.row()).getToken();
    case unsafeDisplayRole:         return m_vpnOrders.at(index.row()).getUnsafe();
    case speedLimitDisplayRole:     return m_vpnOrders.at(index.row()).getSpeedLimit();
    default: break;
    }

    return QVariant();
}

bool VpnOrdersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    switch (role)
    {
    case nameDisplayRole:       m_vpnOrders[index.row()].setName(value.toString()); break;
    case regionDisplayRole:     m_vpnOrders[index.row()].setRegion(value.toString()); break;
    case switchedOnDisplayRole: m_vpnOrders[index.row()].setSwitchedOn(value.toBool()); break;
    case unitsDisplayRole:      m_vpnOrders[index.row()].setUnits(value.toInt()); break;
    case unitsTypeDisplayRole:  m_vpnOrders[index.row()].setUnitsType(VpnOrder::UnitsType(value.toInt())); break;
    case valueDisplayRole:      m_vpnOrders[index.row()].setValue(value.toDouble()); break;
    case tokenDisplayRole:      m_vpnOrders[index.row()].setToken(value.toString()); break;
    case unsafeDisplayRole:     m_vpnOrders[index.row()].setUnsafe(value.toBool()); break;
    case speedLimitDisplayRole: m_vpnOrders[index.row()].setSpeedLimit(value.toInt()); break;
    default: return false;
    }
    emit dataChanged(createIndex(0, 0), createIndex(m_vpnOrders.length(), 0));
    return true;
}

QHash<int, QByteArray> VpnOrdersModel::roleNames() const
{
    static const QHash<int, QByteArray> roles
    {
        {nameDisplayRole,       "name" },
        {regionDisplayRole,     "region" },
        {switchedOnDisplayRole, "switchedOn" },
        {unitsDisplayRole,      "units" },
        {unitsTypeDisplayRole,  "unitsType" },
        {valueDisplayRole,      "value" },
        {tokenDisplayRole,      "token" },
        {unsafeDisplayRole,     "unsafe" },
        {speedLimitDisplayRole, "speedLimit" },
    };

    return roles;
}

VpnOrdersModel::SortType VpnOrdersModel::sortType()
{
    return m_sortType;
}

void VpnOrdersModel::setSortType(VpnOrdersModel::SortType type)
{
    m_sortType = type;

    switch (m_sortType)
    {
    case SortByRegion:
        std::sort(m_vpnOrders.begin(), m_vpnOrders.end(),
                 [](const VpnOrder &a, const VpnOrder &b)
                 {
                     return a.getRegion() < b.getRegion();
                 });
        break;
    case SortByToken:
        std::sort(m_vpnOrders.begin(), m_vpnOrders.end(),
                 [](const VpnOrder &a, const VpnOrder &b)
                 {
                     return a.getToken() < b.getToken();
                 });
        break;
    }

    emit dataChanged(createIndex(0, 0), createIndex(m_vpnOrders.length(), 0));
    emit sortTypeChanged(type);
}
