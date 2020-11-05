#include "DapWalletBalanceModel.h"



DapWalletBalanceModel::DapWalletBalanceModel(QObject *parent)
{

}

void DapWalletBalanceModel::setBalance(WalletBallanceInfo_t a_balanceMap)
{
    QMutableMapIterator<const DapNetwork*, DapBalanceModel*> it(m_networkBalances);
    while (it.hasNext())
    {
        if (!a_balanceMap.contains(it.key()))
            it.remove();
    }

    for (auto it = a_balanceMap.begin(); it != a_balanceMap.end(); ++it)
    {
        this->setBalance(it.key(), it.value());
    }
}

void DapWalletBalanceModel::setBalance(const DapNetwork *a_network, DapBalanceModel::BalanceInfo_t &a_balanceMap)
{
    if (m_networkBalances.contains(a_network))
        m_networkBalances[a_network]->setBalance(a_balanceMap);

    else
        this->insertBalanceModel(a_network, a_balanceMap);
}

int DapWalletBalanceModel::rowCount(const QModelIndex &a_parent) const
{
    Q_UNUSED(a_parent)
    return m_networkBalances.count();
}

QVariant DapWalletBalanceModel::data(const QModelIndex &a_index, int a_role) const
{
    int row = a_index.row();
    if (row < 0 || row > m_networkBalances.count())
        return {};

    auto it = m_networkBalances.begin();
    it += row;

    switch (a_role) {
        case Roles::Network: return it.key()->name();
        case Roles::BalanceModel: return QVariant::fromValue<QObject*>(it.value());
        default: return {};
    }
}

bool DapWalletBalanceModel::insertBalanceModel(const DapNetwork *a_network, const DapBalanceModel::BalanceInfo_t &a_balanceMap)
{
    auto lowerBoundIt = m_networkBalances.lowerBound(a_network);
    if (lowerBoundIt.key() == a_network)
        return false;

    auto index = std::distance(lowerBoundIt, m_networkBalances.begin());
    QAbstractListModel::beginInsertRows(QModelIndex(), index, index);

    m_networkBalances[a_network] = new DapBalanceModel(a_balanceMap, this);

    QAbstractListModel::endInsertRows();

    return true;
}

QHash<int, QByteArray> DapWalletBalanceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Network] = "network";
    roles[BalanceModel] = "balanceModel";
    return roles;
}
