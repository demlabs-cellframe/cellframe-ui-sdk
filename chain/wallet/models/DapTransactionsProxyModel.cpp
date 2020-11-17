#include "DapTransactionsProxyModel.h"
#include <QDebug>

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

void DapTransactionsProxyModel::setDateFilter(const Date a_date)
{
    if (a_date == m_date)
        return;
    m_date = a_date;
    emit dateFilterChanged(m_date);
    invalidateFilter();
}

void DapTransactionsProxyModel::addStatusFilter(const DapTransaction::Status a_status)
{
    if (m_statuses.contains(a_status))
        return;
    m_statuses.push_back(a_status);
    emit statusFilterChanged(m_statuses);
    invalidateFilter();
}

void DapTransactionsProxyModel::removeStatusFilter(const DapTransaction::Status a_status)
{
    if (!m_statuses.contains(a_status))
        return;
    m_statuses.removeOne(a_status);
    emit statusFilterChanged(m_statuses);
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
            if(transaction->date() == QDate::currentDate()) return true;
            else return false;

        case Date::Yesterday:
            if(transaction->date() == QDate::currentDate().addDays(-1)) return true;
            else return false;

        case Date::ThisWeek:
            if(transaction->date() > QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek())
                    && transaction->date() <= QDate::currentDate().addDays(7 - QDate::currentDate().dayOfWeek()))
                return true;
            else return false;

        case Date::LastWeek:
            if(transaction->date() <= QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek())
                    && transaction->date() > QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek() - 7))
                return true;
            else return false;
        }
    }
    else return false;
}
