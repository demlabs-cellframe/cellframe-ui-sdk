#include "DapTransactionsModel.h"
#include <QDebug>
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
    DapTransaction* transaction = m_transactions.at(index.row());
    switch (role)
    {
    case Qt::DisplayRole:
        return QVariant::fromValue<QObject*>(transaction);
    case DateDisplayRole:
        if (transaction->date().date() == QDate::currentDate())
            return tr("Today");
        else if (transaction->date().date() == QDate::currentDate().addDays(-1))
            return tr("Yesterday");
        return QLocale(QLocale::Language::English).toString(transaction->date().date(), "MMMM, d");
    }

    return QVariant();
}

void DapTransactionsModel::append(DapTransaction *a_transaction)
{
    for(auto transaction: m_transactions)
    {
        if(transaction->hash() == a_transaction->hash())
            return;
    }

    int lastIndex = m_transactions.count() ;
    beginInsertRows(QModelIndex(), lastIndex, lastIndex);
    m_transactions.append(a_transaction);
    endInsertRows();
}

QHash<int, QByteArray> DapTransactionsModel::roleNames() const
{
    static const QHash<int, QByteArray> roles
    {
        { Qt::DisplayRole, "display" },
        { DateDisplayRole, "date"    }
    };

    return roles;
}
