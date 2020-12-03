#ifndef DAPTRANSACTIONSMODEL_H
#define DAPTRANSACTIONSMODEL_H

#include <QAbstractListModel>
#include "DapTransaction.h"

class DapTransactionsModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        DateDisplayRole = Qt::UserRole,
        TIME
    };

    explicit DapTransactionsModel(QObject *parent = nullptr);

    DapTransaction* findByHash(const QString& a_hash);
    QModelIndex indexOf(DapTransaction* a_transaction);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void append(DapTransaction* a_transaction);
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<DapTransaction*> m_transactions;
};

#endif // DAPTRANSACTIONSMODEL_H
