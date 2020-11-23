#ifndef DAPWALLETMODEL_H
#define DAPWALLETMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <algorithm>
#include <QList>

#include "DapWallet.h"

class DapWalletModel : public QAbstractListModel
{
    Q_OBJECT


public:
    explicit DapWalletModel(QObject *parent = nullptr);
    Q_PROPERTY(QStringList WalletList READ getWalletList NOTIFY walletListChanged)

    enum DapWalletRole
    {
        NameDisplayRole = Qt::UserRole,
        AddressDisplayRole,
        BalanceDisplayRole,
        IconDisplayRole,
        NetworksDisplayRole,
        TokensDisplayRole,
        WalletsDisplayRole,
        WalletDisplayRole
    };
    Q_ENUM(DapWalletRole)

    static DapWalletModel& getInstance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    QList<QObject*> getTokens(const int aIndex) const;

    QStringList getWalletList() const;

    DapWallet* findByName(const QString& a_name);

signals:
    void walletListChanged(const QStringList& aWalletList);

public slots:

    Q_INVOKABLE void appendWallet(DapWallet *aWallet);
    Q_INVOKABLE void appendToken(const QString& asWalletAddress, DapWalletToken* aToken);
    Q_INVOKABLE void removeWallet(const QString& asWalletAddress);
    Q_INVOKABLE void removeWallet(const int aWalletIndex);

private:
    QList<DapWallet*> m_wallets;

};

#endif // DAPWALLETMODEL_H
