#ifndef DAPWALLETBALLANCEMODEL_H
#define DAPWALLETBALLANCEMODEL_H

#include <QAbstractListModel>
#include <QMultiMap>

#include "DapNetwork.h"
#include "DapToken.h"


class DapWalletBalanceModel : public QAbstractListModel
{
    Q_OBJECT

    typedef ulong balance_t;

    enum Roles
    {
        Network = Qt::UserRole,
        Token,
        Amount
    };

    explicit DapWalletBalanceModel(QObject *parent = nullptr);

public:

    virtual QHash<int, QByteArray> roleNames() const override;
public:
    virtual int rowCount(const QModelIndex &a_parent) const override;
    virtual QVariant data(const QModelIndex &a_index, int a_role) const override;

private:
    QMultiMap<DapNetwork*, QPair<DapToken*, balance_t>> m_tokensCount;

};

#endif // DAPWALLETBALLANCEMODEL_H
