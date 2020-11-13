#ifndef DAPTRANSACTIONSPROXYMODEL_H
#define DAPTRANSACTIONSPROXYMODEL_H

#include <QSortFilterProxyModel>

class DapTransactionsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit DapTransactionsProxyModel(QObject *a_parent = nullptr);
};

#endif // DAPTRANSACTIONSPROXYMODEL_H
