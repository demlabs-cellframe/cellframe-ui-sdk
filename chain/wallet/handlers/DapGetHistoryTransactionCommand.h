#ifndef DAPGETHISTORYTRANSACTIONCOMMAND_H
#define DAPGETHISTORYTRANSACTIONCOMMAND_H

#include <QProcess>
#include <QString>
#include "DapErrors.h"
#include <QDateTime>

#include "DapAbstractCommand.h"

class DapGetHistoryTransactionCommand : public DapAbstractCommand
{
public:
    static const QString TransactionTime;
    static const QString TransactionAction;
    static const QString TransactionAmount;
    static const QString TransactionTokenName;
    static const QString TransactionAddress;
    static const QString TransactionHash;

    enum Action{GET,GIVE};
    /// Overloaded constructor.
    /// @param asServiceName Service name.
    /// @param parent Parent.
    /// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
    /// @param asCliPath The path to cli nodes.
    DapGetHistoryTransactionCommand(const QString &asServicename, QObject *parent = nullptr, const QString &asCliPath = QString());

public slots:
    /// Send a response to the client.
    /// @details Performed on the service side.
    /// @param arg1 name Wallet
    /// @param arg2 natwork
    /// @param arg3 chain
    /// @param arg4
    /// @param arg5
    /// @param arg6
    /// @return Reply to client.
    QVariant respondToClient(const QVariant &arg1 = QVariant(), const QVariant &arg2 = QVariant(),    //original
                             const QVariant &arg3 = QVariant(), const QVariant &arg4 = QVariant(),
                             const QVariant &arg5 = QVariant(), const QVariant &arg6 = QVariant(),
                             const QVariant &arg7 = QVariant(), const QVariant &arg8 = QVariant(),
                             const QVariant &arg9 = QVariant(), const QVariant &arg10 = QVariant()) override;

    const QStringList m_month{"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
};

#endif // DAPGETHISTORYTRANSACTIONCOMMAND_H
