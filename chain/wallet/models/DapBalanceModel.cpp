#include "DapBalanceModel.h"



DapBalanceModel::DapBalanceModel(QObject *parent)
{
}

DapBalanceModel::DapBalanceModel(const BalanceInfo_t &a_balanceMap, QObject *a_parent)
    :DapBalanceModel(a_parent)
{
    this->setBalance(a_balanceMap);
}

void DapBalanceModel::setBalance(const BalanceInfo_t &a_balanceMap)
{
    //remove not existing in a_balanceMap
    QMutableMapIterator<BalanceInfo_t::key_type,  BalanceInfo_t::mapped_type> it(m_tokensAmount);
    while (it.hasNext())
    {
        it.next();

        if (!a_balanceMap.contains(it.key()))
        {
            int row = this->rowOf(it.key());
            this->QAbstractListModel::beginRemoveRows({}, row, row);
            it.remove();
            this->endRemoveRows();
        }
    }

    for (auto it = a_balanceMap.begin(); it != a_balanceMap.end(); ++it)
    {
        this->setBalance(it.key(), it.value());
    }
}

void DapBalanceModel::setBalance(const DapToken *a_token, balance_t a_amount)
{
    auto tokenIt = m_tokensAmount.find(a_token);

    //if already exist:
    if (tokenIt == m_tokensAmount.end())
    {
        this->insertTokenAmount(a_token, a_amount);
        return;
    }

    int row = this->rowOf(tokenIt);
    QModelIndex index = this->index(row, 0);

    //remove token if balance is empty:
    if (a_amount == 0)
    {
        beginRemoveRows(QModelIndex(), row, row);
        m_tokensAmount.erase(tokenIt);
        endRemoveRows();
    }
    else
    {
        tokenIt.value() = a_amount;
        emit this->QAbstractListModel::dataChanged(index, index);
    }
}

int DapBalanceModel::balance(const QString& a_tokenName) const
{
    return m_tokensAmount.value(DapToken::token(a_tokenName));
}

int DapBalanceModel::rowCount(const QModelIndex &a_parent) const
{
    Q_UNUSED(a_parent)
    return m_tokensAmount.count();
}

QVariant DapBalanceModel::data(const QModelIndex &a_index, int a_role) const
{
    int row = a_index.row();
    if (row < 0 || row > m_tokensAmount.count())
        return {};

    auto it = m_tokensAmount.begin();
    it += row;

    switch (a_role) {
        case Roles::Token: return QVariant(it.key()->name());
        case Roles::Amount: return QVariant::fromValue<balance_t>(it.value());
        default: return {};
    }
}

QVariantList DapBalanceModel::tokens() const
{
    QVariantList tokens;
    for (auto curToken: m_tokensAmount.keys())
    {
        tokens.append(QVariant::fromValue(const_cast<DapToken*>(curToken)));
    }
    return tokens;
}

bool DapBalanceModel::insertTokenAmount(const DapToken *a_token, balance_t a_amount)
{
    auto lowerBoundIt = m_tokensAmount.lowerBound(a_token);
    if (lowerBoundIt.key() == a_token)
        return false;

    int index = this->rowOf(lowerBoundIt);

    QAbstractListModel::beginInsertRows(QModelIndex(), index, index);

    m_tokensAmount[a_token] = a_amount;

    emit this->tokensChanged(this->tokens());

    QAbstractListModel::endInsertRows();

    return true;
}

int DapBalanceModel::rowOf(const DapToken *a_token)
{
    auto it = m_tokensAmount.find(a_token);
    if (it == m_tokensAmount.end())
        return -1;

    return this->rowOf(it);
}

int DapBalanceModel::rowOf(BalanceInfo_t::iterator a_iterator)
{
    if (m_tokensAmount.isEmpty())
        return 0;

    return std::distance(m_tokensAmount.begin(), a_iterator);
}


QHash<int, QByteArray> DapBalanceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Token] = "token";
    roles[Amount] = "amount";
    return roles;
}
