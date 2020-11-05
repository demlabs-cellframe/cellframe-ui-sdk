#ifndef DAPWALLETBALLANCEMODEL_H
#define DAPWALLETBALLANCEMODEL_H

#include <QAbstractListModel>
#include <QMultiMap>

#include "DapNetwork.h"
#include "DapToken.h"
#include "DapBalanceModel.h"

class DapWalletBalanceModel : public QAbstractListModel
{
    Q_OBJECT

    enum Roles
    {
        Network = Qt::UserRole,
        BalanceModel
    };

public:
    typedef  QMap<const DapNetwork*, DapBalanceModel::BalanceInfo_t> WalletBallanceInfo_t;
    explicit DapWalletBalanceModel(QObject *parent = nullptr);

    void setBalance(WalletBallanceInfo_t a_balanceMap);
    void setBalance(const DapNetwork *a_network, DapBalanceModel::BalanceInfo_t &a_balanceMap);

    virtual QHash<int, QByteArray> roleNames() const override;

    virtual int rowCount(const QModelIndex &a_parent) const override;
    virtual QVariant data(const QModelIndex &a_index, int a_role) const override;

private:
    QMap<const DapNetwork*, DapBalanceModel*> m_networkBalances;

    bool insertBalanceModel(const DapNetwork *a_network, const DapBalanceModel::BalanceInfo_t& a_balanceMap);

};

#endif // DAPWALLETBALLANCEMODEL_H
