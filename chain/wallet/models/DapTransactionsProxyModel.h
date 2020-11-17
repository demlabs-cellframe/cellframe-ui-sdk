#ifndef DAPTRANSACTIONSPROXYMODEL_H
#define DAPTRANSACTIONSPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "DapTransactionsModel.h"
#include "DapTransaction.h"

class DapTransactionsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(DapTransactionsProxyModel::Date dateFilter   READ dateFilter   WRITE setDateFilter NOTIFY dateFilterChanged)
    Q_PROPERTY(QVariantList                    statusFilter READ statusFilter NOTIFY statusFilterChanged)

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

    DapTransactionsProxyModel::Date dateFilter()   const { return m_date; }
    QVariantList statusFilter() const;

    void setDateFilter(const DapTransactionsProxyModel::Date a_date = DapTransactionsProxyModel::Date::AllTime);
    Q_INVOKABLE void addStatusFilter(const DapTransaction::Status a_status);
    Q_INVOKABLE void removeStatusFilter(const DapTransaction::Status a_status);

signals:
    void dateFilterChanged(DapTransactionsProxyModel::Date);
    void statusFilterChanged(QVector<DapTransaction::Status>);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;

private:
    Date m_date = Date::AllTime;
    QVector<DapTransaction::Status> m_statuses
    {
        DapTransaction::Status::Local,
        DapTransaction::Status::Mempool,
        DapTransaction::Status::Successful,
        DapTransaction::Status::Canceled
    };
};

#endif // DAPTRANSACTIONSPROXYMODEL_H
