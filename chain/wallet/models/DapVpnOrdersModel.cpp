#include "DapVpnOrdersModel.h"

DapVpnOrdersModel::DapVpnOrdersModel(QObject *parent): QAbstractListModel(parent)
{

}

DapVpnOrdersModel &DapVpnOrdersModel::instance()
{
    static DapVpnOrdersModel inst;
    return inst;
}

int DapVpnOrdersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_orders.count();
}

QVariant DapVpnOrdersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case NameDisplayRole:
        return m_orders.at(index.row()).name();
    case DateDisplayRole:
        return m_orders.at(index.row()).date();
    case UnitsDisplayRole:
        return m_orders.at(index.row()).units();
    case TypeDisplayRole:
        return m_orders.at(index.row()).type();
    case ValueDisplayRole:
        return m_orders.at(index.row()).value();
    case TokenDisplayRole:
        return m_orders.at(index.row()).token();
    default: break;
    }
    return QVariant();
}

QHash<int, QByteArray> DapVpnOrdersModel::roleNames() const
{
    static const QHash<int, QByteArray> roles
    {
        { NameDisplayRole, "Custom name" },
        { DateDisplayRole, "Date created" },
        { UnitsDisplayRole, "Units" },
        { TypeDisplayRole,  "Units type" },
        { ValueDisplayRole, "Value" },
        { TokenDisplayRole, "Token" }
    };

    return roles;

}

void DapVpnOrdersModel::append(const DapVpnOrder &a_order)
{
    m_orders.append(a_order);

    int lastIndex = m_orders.count() - 1;
    beginInsertRows(QModelIndex(), lastIndex, lastIndex);
    endInsertRows();
}
