#include "DapTransactionsProxyModel.h"
#include <QLocale>

DapTransactionsProxyModel::DapTransactionsProxyModel(QObject *a_parent)
    : QSortFilterProxyModel(a_parent)
{
}

DapTransactionsProxyModel::DapTransactionsProxyModel(QAbstractListModel *a_model,
                                                     QObject *a_parent)
    : QSortFilterProxyModel(a_parent)
{
    setSourceModel(a_model);
}

QVariantList DapTransactionsProxyModel::statusFilter() const
{
    QVariantList list;
    for(const DapTransaction::Status el:m_statuses)
        list << QVariant::fromValue(el);
    return list;
}

void DapTransactionsProxyModel::setDateFilter(int a_date)
{
    if (a_date == m_date)
        return;
    m_date = a_date;
    emit dateFilterChanged(m_date);
    invalidateFilter();
}

void DapTransactionsProxyModel::addStatusFilter(int a_status)
{
    if (m_statuses.contains(static_cast<DapTransaction::Status>(a_status)))
        return;
    m_statuses.push_back(static_cast<DapTransaction::Status>(a_status));
    emit statusFilterChanged(m_statuses);
    invalidateFilter();
}

void DapTransactionsProxyModel::removeStatusFilter(int a_status)
{
    if (!m_statuses.contains(static_cast<DapTransaction::Status>(a_status)))
        return;
    m_statuses.removeOne(static_cast<DapTransaction::Status>(a_status));
    emit statusFilterChanged(m_statuses);
    invalidateFilter();
}

bool DapTransactionsProxyModel::needShowDate(int a_index)
{
    if (a_index < 0 || a_index >= this->rowCount()) return false;
    if (a_index == 0) return true;
    QModelIndex leftIndex = this->index(a_index - 1, 0);
    QModelIndex rigntIndex = this->index(a_index, 0);
    DapTransaction* leftTransaction = qobject_cast<DapTransaction*>(
                qvariant_cast<QObject*>(this->data(leftIndex)));
    DapTransaction* rightTransaction = qobject_cast<DapTransaction*>(
                qvariant_cast<QObject*>(this->data(rigntIndex)));
    return leftTransaction->date().date() != rightTransaction->date().date();
}

QString DapTransactionsProxyModel::displayDate(int a_index)
{
    if (a_index < 0 || a_index >= this->rowCount()) return "";
    QModelIndex index = this->index(a_index, 0);
    DapTransaction* transaction = qobject_cast<DapTransaction*>(
                qvariant_cast<QObject*>(this->data(index)));
    if (transaction->date().date() == QDate::currentDate())
        return tr("Today");
    else if (transaction->date().date() == QDate::currentDate().addDays(-1))
        return tr("Yesterday");
    return QLocale(QLocale::Language::English).toString(transaction->date().date(), "MMMM, d");
}

void DapTransactionsProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);
    this->sort(0,Qt::SortOrder::DescendingOrder);
}

void DapTransactionsProxyModel::setDefaultFilters()
{
    if (!m_statuses.contains(DapTransaction::Status::Local))
        m_statuses.push_back(DapTransaction::Status::Local);
    if (!m_statuses.contains(DapTransaction::Status::Mempool))
        m_statuses.push_back(DapTransaction::Status::Mempool);
    if (!m_statuses.contains(DapTransaction::Status::Canceled))
        m_statuses.push_back(DapTransaction::Status::Canceled);
    if (!m_statuses.contains(DapTransaction::Status::Successful))
        m_statuses.push_back(DapTransaction::Status::Successful);
    m_date = Date::AllTime;
    invalidateFilter();
}

bool DapTransactionsProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex modelIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    QObject* obj = qvariant_cast<QObject*>(sourceModel()->data(modelIndex));
    DapTransaction* transaction = qobject_cast<DapTransaction*>(obj);
    if (m_statuses.contains(transaction->status()))
    {
        switch (m_date)
        {
        case Date::AllTime:
            return true;

        case Date::Today:
            return transaction->date().date() == QDate::currentDate();

        case Date::Yesterday:
            return transaction->date().date() == QDate::currentDate().addDays(-1);

        case Date::ThisWeek:
            return transaction->date().date() > QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek())
                    && transaction->date().date() <= QDate::currentDate().addDays(7 - QDate::currentDate().dayOfWeek());

        case Date::LastWeek:
            return transaction->date().date() <= QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek())
                    && transaction->date().date() > QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek() - 7);
        }
    }
    return false;
}

bool DapTransactionsProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QObject* obj = qvariant_cast<QObject*>(sourceModel()->data(source_left));
    DapTransaction* left_transaction = qobject_cast<DapTransaction*>(obj);
    obj = qvariant_cast<QObject*>(sourceModel()->data(source_right));
    DapTransaction* right_transaction = qobject_cast<DapTransaction*>(obj);
    return left_transaction->date() < right_transaction->date();
}
