#include "DapWalletBalanceModel.h"



DapWalletBalanceModel::DapWalletBalanceModel(QObject *parent)
{

}

int DapWalletBalanceModel::rowCount(const QModelIndex &a_parent) const
{
    Q_UNUSED(a_parent)
    return m_tokensCount.count();
}

QVariant DapWalletBalanceModel::data(const QModelIndex &a_index, int a_role) const
{
    int row = a_index.row();
    if (row < 0 || row > m_tokensCount.count())
        return {};

    auto it = m_tokensCount.begin();
    it += row;

    switch (a_role) {
        case Roles::Network: return it.key()->name();
        case Roles::Token: return QVariant::fromValue<QObject*>(it.value().first);
        case Roles::Amount: return QVariant::fromValue<balance_t>(it.value().second);
        default: return {};
    }
}


QHash<int, QByteArray> DapWalletBalanceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Network] = "network";
    roles[Token] = "token";
    roles[Amount] = "amount";
    return roles;
}
