#include "DapBalanceModel.h"



DapBalanceModel::DapBalanceModel(QObject *a_parent)
    : QAbstractListModel(a_parent)
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
    QMutableListIterator<DapTokenValue*> it(m_tokensAmount);
    while (it.hasNext())
    {
        it.next();

        if (!a_balanceMap.contains(it.value()->token()))
        {
            int row = m_tokensAmount.indexOf(it.value());
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
    //if already exist:
    if (this->appendTokenAmount(a_token, a_amount))
        return;

    auto tokenVal = this->tokenValue(a_token);

    //remove token if balance is empty:
    if (a_amount == 0)
    {
        int row = m_tokensAmount.indexOf(tokenVal);
        beginRemoveRows(QModelIndex(), row, row);
        m_tokensAmount.removeAt(row);
        endRemoveRows();
    }
    else
        tokenVal->setAmount(a_amount);
}

bool DapBalanceModel::hasBalance(const QString &a_tokenName, const QString &a_tokenAmountString) const
{
    auto token = DapToken::token(a_tokenName);
    if (!token)
        return 0;
    auto tokenBalance = this->balance(token);

    auto requestedAmount = DapTokenValue::tokensAmountStringtoTokensAmount(a_tokenAmountString);

    return  (requestedAmount <= tokenBalance);
}

balance_t DapBalanceModel::balance(const DapToken* a_token) const
{
    auto tokenVal = this->tokenValue(a_token);

    if (!tokenVal)
        return 0;

    return tokenVal->amount();
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

    switch (a_role) {
        case Roles::TOKEN_VALUE: return QVariant::fromValue(const_cast<DapTokenValue*>(m_tokensAmount.at(a_index.row())));
        default: return {};
    }
}

QVariantList DapBalanceModel::tokens() const
{
    QVariantList tokens;
    for (auto curTokenValue: m_tokensAmount)
    {
        tokens.append(QVariant::fromValue(curTokenValue->token()));
    }
    return tokens;
}

DapTokenValue *DapBalanceModel::tokenValue(const DapToken* a_token) const
{
    for (auto& curTokenValue: m_tokensAmount)
    {
        if (curTokenValue->token() == a_token)
            return curTokenValue;
    }
    return nullptr;
}


bool DapBalanceModel::appendTokenAmount(const DapToken *a_token, balance_t a_amount)
{
    if (this->tokenValue(a_token))
        return false;

    int index = m_tokensAmount.count();

    QAbstractListModel::beginInsertRows(QModelIndex(), index, index);

    m_tokensAmount.append(new DapTokenValue(a_token, a_amount));

    emit this->tokensChanged(this->tokens());

    QAbstractListModel::endInsertRows();

    return true;
}


QHash<int, QByteArray> DapBalanceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TOKEN_VALUE] = "tokenValue";
    return roles;
}
