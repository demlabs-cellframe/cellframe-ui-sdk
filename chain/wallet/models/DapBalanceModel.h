#ifndef DAPBALLANCEMODEL_H
#define DAPBALLANCEMODEL_H

#include <QAbstractListModel>
#include <QMultiMap>

#include "DapNetwork.h"
#include "DapToken.h"

typedef ulong balance_t;

class DapBalanceModel : public QAbstractListModel
{
    Q_OBJECT



    enum Roles
    {
        Token = Qt::UserRole,
        Amount
    };

public:
    typedef QMap<const DapToken *, balance_t> BalanceInfo_t;

    explicit DapBalanceModel(QObject *parent = nullptr);
    explicit DapBalanceModel(const BalanceInfo_t& a_balanceMap, QObject *a_parent = nullptr);

    void setBalance(const BalanceInfo_t &a_balanceMap);
    void setBalance(const DapToken* a_token, balance_t a_amount);

    virtual QHash<int, QByteArray> roleNames() const override;

    virtual int rowCount(const QModelIndex &a_parent) const override;
    virtual QVariant data(const QModelIndex &a_index, int a_role) const override;

private:
    bool insertTokenAmount(const DapToken *a_token, balance_t a_amount);

    int rowOf(const DapToken* a_token);
    int rowOf(BalanceInfo_t::iterator a_iterator);

    BalanceInfo_t m_tokensAmount;
};

#endif // DAPBALLANCEMODEL_H
