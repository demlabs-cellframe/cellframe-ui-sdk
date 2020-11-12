#include "DapVpnOrdersModel.h"

DapVpnOrdersModel::DapVpnOrdersModel(QObject *parent): QAbstractListModel(parent)
{

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
    case Qt::DisplayRole:
        return QVariant::fromValue(m_orders.at(index.row()));
    case NameDisplayRole:
        return m_orders.at(index.row())->name();
    case DateDisplayRole:
        return m_orders.at(index.row())->date().toString();
    case UnitsDisplayRole:
        return QString::number(m_orders.at(index.row())->units());
    case TypeDisplayRole:
        return m_orders.at(index.row())->type();
    case TokenValueDisplayRole:
        return QVariant::fromValue<QObject*>(m_orders.at(index.row())->tokenValue());
    }
    return QVariant();
}

QHash<int, QByteArray> DapVpnOrdersModel::roleNames() const
{
    static const QHash<int, QByteArray> roles
    {
        { NameDisplayRole,       "name"       },
        { DateDisplayRole,       "date"       },
        { UnitsDisplayRole,      "units"      },
        { TypeDisplayRole,       "type"       },
        { TokenValueDisplayRole, "tokenValue" }
    };

    return roles;

}

void DapVpnOrdersModel::append(DapVpnOrder* a_order)
{
    int lastIndex = m_orders.count() - 1;
    beginInsertRows(QModelIndex(), lastIndex, lastIndex);
    m_orders.append(a_order);
    endInsertRows();
}
