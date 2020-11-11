#include "DapTransactionsModel.h"

DapTransactionsModel::DapTransactionsModel(QObject* a_parent)
    : QAbstractListModel(a_parent)
{ 
}

int DapTransactionsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_transactions.count();
}

QVariant DapTransactionsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    switch (role)
    {
    case Qt::DisplayRole:
        return QVariant::fromValue(m_transactions.at(index.row()));
    case NetworkDisplayRole:
        return QVariant::fromValue<QObject*>(m_transactions.at(index.row())->network());
    case StatusDisplayRole:
        return QVariant();
    case ConfirmationsCountDisplayRole:
        return QVariant();
    case TokenValueDisplayRole:
        return QVariant();
    }

    return QVariant();
}

QHash<int, QByteArray> DapTransactionsModel::roleNames() const
{
    static const QHash<int, QByteArray> roles
    {
        { NetworkDisplayRole,            "network"            },
        { StatusDisplayRole,             "status"             },
        { ConfirmationsCountDisplayRole, "confirmationsCount" },
        { TokenValueDisplayRole,         "tokenValue"         }
    };
    return roles;
}
