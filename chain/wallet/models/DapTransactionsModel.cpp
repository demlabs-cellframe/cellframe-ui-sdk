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
    switch (role)
    {
    case Qt::DisplayRole:
        return QVariant::fromValue<QObject*>(m_transactions.at(index.row()));
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
