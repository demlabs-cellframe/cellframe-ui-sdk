#ifndef DAPTRANSACTIONSMODEL_H
#define DAPTRANSACTIONSMODEL_H

#include <QAbstractListModel>
#include "DapTransaction.h"

class DapTransactionsModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum DapTransactionsRoles {
        TransactionDisplayRole = 1
    }; Q_ENUM(DapTransactionsRoles)

    explicit DapTransactionsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void append(DapTransaction* a_transaction);

private:
    QList<DapTransaction*> m_transactions;
};

#endif // DAPTRANSACTIONSMODEL_H
