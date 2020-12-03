#ifndef DAPBALLANCEMODEL_H
#define DAPBALLANCEMODEL_H

#include <QAbstractListModel>
#include <QMap>
#include <QSet>

#include "DapNetwork.h"
#include "DapToken.h"
#include "DapTokenValue.h"

class DapBalanceModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList tokens READ tokens NOTIFY tokensChanged)
    enum Roles
    {
        TOKEN_VALUE = Qt::UserRole
    };

public:
    typedef QMap<const DapToken *, balance_t> BalanceInfo_t;

    explicit DapBalanceModel(QObject *a_parent = nullptr);
    explicit DapBalanceModel(const BalanceInfo_t& a_balanceMap, QObject *a_parent = nullptr);

    void setBalance(const BalanceInfo_t &a_balanceMap);
    void setBalance(const DapToken* a_token, balance_t a_amount);

    Q_INVOKABLE bool hasBalance(const QString &a_tokenName, const QString &a_tokenAmountString) const;
    balance_t balance(const DapToken *a_token) const;

    virtual QHash<int, QByteArray> roleNames() const override;

    virtual int rowCount(const QModelIndex &a_parent) const override;
    virtual QVariant data(const QModelIndex &a_index, int a_role) const override;

    QVariantList tokens() const;
    DapTokenValue* tokenValue(const DapToken *a_token) const;


signals:
    void tokensChanged(const QVariantList& a_model);

private:
    bool appendTokenAmount(const DapToken *a_token, balance_t a_amount);

    QList<DapTokenValue*> m_tokensAmount;
};

Q_DECLARE_METATYPE(DapBalanceModel*)

#endif // DAPBALLANCEMODEL_H
