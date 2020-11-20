#ifndef DAPTRANSACTIONSPROXYMODEL_H
#define DAPTRANSACTIONSPROXYMODEL_H

#include <QSortFilterProxyModel>
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
    explicit DapTransactionsProxyModel(QAbstractListModel* a_model,
                                       QObject *a_parent = nullptr);

    int dateFilter()   const { return m_date; }
    QVariantList statusFilter() const;

    void setDateFilter(int a_date = DapTransactionsProxyModel::Date::AllTime);
    Q_INVOKABLE void addStatusFilter(int a_status);
    Q_INVOKABLE void removeStatusFilter(int a_status);

    Q_INVOKABLE bool needShowDate(int a_index);
    Q_INVOKABLE QString displayDate(int a_index);
    void setSourceModel(QAbstractItemModel *sourceModel) override;

signals:
    void dateFilterChanged(int);
    void statusFilterChanged(QVector<DapTransaction::Status>);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

private:
    int m_date = Date::AllTime;
    QVector<DapTransaction::Status> m_statuses
    {
        DapTransaction::Status::Local,
        DapTransaction::Status::Mempool,
        DapTransaction::Status::Successful,
        DapTransaction::Status::Canceled
    };
};

#endif // DAPTRANSACTIONSPROXYMODEL_H
