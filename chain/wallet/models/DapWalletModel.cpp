#include "DapWalletModel.h"

DapWalletModel::DapWalletModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

DapWalletModel &DapWalletModel::getInstance()
{
    static DapWalletModel instance;
    return instance;
}

int DapWalletModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_wallets.count();
}

QVariant DapWalletModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
        case NameDisplayRole:       return m_wallets[index.row()]->getName();
        case BalanceDisplayRole:    return m_wallets[index.row()]->getBalance();
        case AddressDisplayRole:    return m_wallets[index.row()]->getAddress();
        case IconDisplayRole:       return m_wallets[index.row()]->getIcon();
        case NetworksDisplayRole:   return m_wallets[index.row()]->getNetworks();
        case TokensDisplayRole:
            return QVariant::fromValue<QList<QObject*>>(getTokens(index.row()));
        case WalletsDisplayRole:    return getWalletList();
        case WalletDisplayRole:
            return QVariant::fromValue<QObject*>(m_wallets[index.row()]);
        default: break;
    }

    return QVariant();
}

QList<QObject*> DapWalletModel::getTokens(const int aIndex) const
{
    QList<QObject*> tokens;
    auto cbegin = m_wallets[aIndex]->getTokens().cbegin();
    auto cend = m_wallets[aIndex]->getTokens().cend();
    for(; cbegin != cend; ++ cbegin)
        tokens.append(*cbegin);

    return tokens;
}

QStringList DapWalletModel::getWalletList() const
{
    QStringList walletList;
    foreach (auto wallet, m_wallets)
    {
        walletList.append(wallet->getName());
    }
    return walletList;
}

DapWallet *DapWalletModel::findByName(const QString &a_name)
{
    auto it = std::find_if(m_wallets.begin(), m_wallets.end(), [&a_name] (DapWallet* a_wallet)
    {
        return a_wallet->getName() == a_name;
    });
    if (it == m_wallets.end())
        return nullptr;

    return *it;
}

void DapWalletModel::appendWallet(DapWallet* aWallet)
{
    m_wallets.append(aWallet);

    emit walletListChanged(getWalletList());

    int lastIndex = m_wallets.count();
    beginInsertRows(QModelIndex(), lastIndex, lastIndex);
    endInsertRows();
}

void DapWalletModel::appendToken(const QString &asWalletAddress, DapWalletToken* aToken)
{
    auto wallet = std::find_if(m_wallets.begin(), m_wallets.end(), [=] (DapWallet* aWallet)
    {
        return aWallet->getAddresses().values().contains(asWalletAddress);
    });

    return (*wallet)->addToken(aToken);
}

void DapWalletModel::removeWallet(const QString &asWalletAddress)
{
    int removeIndex = -1;
    auto wallet = std::find_if(m_wallets.cbegin(), m_wallets.cend(), [=] (DapWallet* aWallet)
    {
        return aWallet->getAddresses().values().contains(asWalletAddress);
    });
    removeIndex = m_wallets.indexOf(*wallet);
    m_wallets.removeAt(removeIndex);

    emit walletListChanged(getWalletList());

    if(removeIndex == -1)
        return;
    beginRemoveRows(QModelIndex(), removeIndex, removeIndex);
    endRemoveRows();
}

void DapWalletModel::removeWallet(const int aWalletIndex)
{
    if(aWalletIndex >= m_wallets.count() || m_wallets.count() < aWalletIndex)
        return;
    beginRemoveRows(QModelIndex(), aWalletIndex, aWalletIndex);
    m_wallets.removeAt(aWalletIndex);

    emit walletListChanged(getWalletList());

    endRemoveRows();
}

QHash<int, QByteArray> DapWalletModel::roleNames() const
{
    static const QHash<int, QByteArray> roles
    {
        { NameDisplayRole,      "name"       },
        { BalanceDisplayRole,   "balance"    },
        { AddressDisplayRole,   "address"    },
        { IconDisplayRole,      "iconPath"   },
        { NetworksDisplayRole,  "networks"   },
        { TokensDisplayRole,    "tokens"     },
        { WalletsDisplayRole,   "walletList" },
        { WalletDisplayRole,    "wallet"     }
    };

    return roles;
}
