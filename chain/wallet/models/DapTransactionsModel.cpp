#include "DapTransactionsModel.h"
#include <QDebug>
DapTransactionsModel::DapTransactionsModel(QObject* a_parent)
    : QAbstractListModel(a_parent)
{
}

DapTransaction *DapTransactionsModel::findByHash(const QString &a_hash)
{
    for (auto curTx: m_transactions)
    {
        if (curTx->hash() == a_hash)
            return curTx;
    }
    return nullptr;
}

QModelIndex DapTransactionsModel::indexOf(DapTransaction *a_transaction)
{
    auto row = m_transactions.indexOf(a_transaction);

    if (row == -1)
        return {};

    return this->index(row);
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
            return QVariant::fromValue(transaction);
        case DateDisplayRole:
        {
            auto txDate = transaction->date().date();
            if (!txDate.isValid())
                return "";
            else if (transaction->date().date() == QDate::currentDate())
                return tr("Today");
            else if (transaction->date().date() == QDate::currentDate().addDays(-1))
                return tr("Yesterday");

            return QLocale(QLocale::Language::English).toString(transaction->date().date(), "MMMM, d");
        }
        case TIME:
            return QVariant::fromValue(transaction->date());

    }

    return QVariant();
}

void DapTransactionsModel::append(DapTransaction *a_transaction)
{
    int lastIndex = m_transactions.count() ;
    beginInsertRows(QModelIndex(), lastIndex, lastIndex);
    m_transactions.append(a_transaction);
    endInsertRows();

    connect(a_transaction, &DapTransaction::dateChanged, [this, a_transaction]{
        auto index = indexOf(a_transaction);
        emit this->dataChanged(index, index, {Roles::TIME, Roles::DateDisplayRole});
    });
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
