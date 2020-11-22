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
    Q_PROPERTY(QVariantList networks READ networks NOTIFY networksChanged)
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)

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

    QVariantList networks();

    bool isEmpty();

    Q_INVOKABLE DapBalanceModel* getBalanceModel(const QString& a_networkName);

signals:
    void networksChanged(QVariantList a_model);
    void isEmptyChanged(bool a_isEmpty);


private:
    QMap<const DapNetwork*, DapBalanceModel*> m_networkBalances;

    bool insertBalanceModel(const DapNetwork *a_network, const DapBalanceModel::BalanceInfo_t& a_balanceMap);

};

Q_DECLARE_METATYPE(DapWalletBalanceModel*)

#endif // DAPWALLETBALLANCEMODEL_H
