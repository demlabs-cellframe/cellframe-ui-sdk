#include "VpnOrdersModel.h"

VpnOrdersModel::VpnOrdersModel(QObject *parent)
    : QAbstractListModel(parent)
{
    VpnOrder order1{"Auto server",  "Europe",       false,  567,    "seconds",  63,         "LSDO", false,  1};
    VpnOrder order2{"Auto Asia",    "England",      false,  3600,   "hours",    0.1,        "LFDF", false,  -1};
    VpnOrder order3{"Auto Europe",  "Asia",         false,  1230,   "minutes",  48,         "ASAD", true,   1};
    VpnOrder order4{"Auto USA",     "Germany",      false,  854,    "hours",    135.688,    "APSF", true,   -1};
    VpnOrder order5{"Auto server",  "Auto",         false,  6532,   "seconds",  891.5,      "POAS", false,  1};
    VpnOrder order6{"Auto server",  "Russian",      false,  3521,   "minutes",  79,         "CSDC", true,   1};
    VpnOrder order7{"Auto server",  "Kazakhstan",   false,  655,    "seconds",  123.56,     "AFSG", false,  -1};
    VpnOrder order8{"Auto server",  "USA",          false,  186,    "minutes",  0.56,       "AWER", true,   1};
    VpnOrder order9{"Auto server",  "Canada",       false,  10,     "hours",    1.153,      "NDGF", false,  -1};

    m_aOrders.append(order1);
    m_aOrders.append(order2);
    m_aOrders.append(order3);
    m_aOrders.append(order4);
    m_aOrders.append(order5);
    m_aOrders.append(order6);
    m_aOrders.append(order7);
    m_aOrders.append(order8);
    m_aOrders.append(order9);
}

void VpnOrdersModel::sortByToken()
{
    std::sort(m_aOrders.begin(), m_aOrders.end(), [](const VpnOrder &a, const VpnOrder &b)
    {
        return a.getToken() < b.getToken();
    });
    emit dataChanged(createIndex(0, 0), createIndex(m_aOrders.length(), 0));
}

void VpnOrdersModel::sortByRegion()
{
    std::sort(m_aOrders.begin(), m_aOrders.end(), [](const VpnOrder &a, const VpnOrder &b)
    {
        return a.getRegion() < b.getRegion();
    });
    emit dataChanged(createIndex(0, 0), createIndex(m_aOrders.length(), 0));
}

VpnOrdersModel *VpnOrdersModel::getInstance()
{
    static VpnOrdersModel *instance = new VpnOrdersModel;
    return instance;
}

int VpnOrdersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_aOrders.count();
}

QVariant VpnOrdersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case nameDisplayRole:           return m_aOrders.at(index.row()).getName();
    case regionDisplayRole:         return m_aOrders.at(index.row()).getToken();
    case switchedOnDisplayRole:     return m_aOrders.at(index.row()).getSwitchedOn();
    case unitsDisplayRole:          return m_aOrders.at(index.row()).getUnits();
    case unitsTypeDisplayRole:      return m_aOrders.at(index.row()).getUnitsType();
    case valueDisplayRole:          return m_aOrders.at(index.row()).getValue();
    case tokenDisplayRole:          return m_aOrders.at(index.row()).getToken();
    case unsafeDisplayRole:         return m_aOrders.at(index.row()).getUnsafe();
    case speedLimitDisplayRole:     return m_aOrders.at(index.row()).getSpeedLimit();
    default: break;
    }

    return QVariant();
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
