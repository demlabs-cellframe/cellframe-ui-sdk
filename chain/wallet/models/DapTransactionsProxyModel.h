#ifndef DAPTRANSACTIONSPROXYMODEL_H
#define DAPTRANSACTIONSPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QSet>
#include "DapTransactionsModel.h"
#include "DapTransaction.h"

class DapTransactionsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int          dateFilter   READ dateFilter   WRITE setDateFilter NOTIFY dateFilterChanged)
    Q_PROPERTY(QVariantList statusFilter READ statusFilter NOTIFY statusFilterChanged)

public:

    enum Date
    {
        AllTime,
        Today,
        Yesterday,
        ThisWeek,
        LastWeek
    }; Q_ENUM(Date)

    explicit DapTransactionsProxyModel(QObject *a_parent = nullptr);

    int dateFilter()   const { return m_date; }
    QVariantList statusFilter() const;

    void setDateFilter(int a_date = DapTransactionsProxyModel::Date::AllTime);
    Q_INVOKABLE void addStatusFilter(int a_status);
    Q_INVOKABLE void removeStatusFilter(int a_status);

    DapTransactionsModel* transactionsModel();

    void setSourceModel(QAbstractItemModel *sourceModel) override;
    void setDefaultFilters();

signals:
    void dateFilterChanged(int);
    void statusFilterChanged(QSet<DapTransaction::Status>);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;

private:
    int m_date = Date::AllTime;
    QSet<DapTransaction::Status> m_statuses
    {
        DapTransaction::Status::LOCAL,
        DapTransaction::Status::MEMPOOL,
        DapTransaction::Status::SUCCESSFUL,
        DapTransaction::Status::CANCELED
    };
};

#endif // DAPTRANSACTIONSPROXYMODEL_H
