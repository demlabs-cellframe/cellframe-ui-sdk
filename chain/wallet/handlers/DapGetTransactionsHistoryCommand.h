#pragma once

#include <QProcess>
#include <QString>
#include "DapErrors.h"
#include <QDateTime>
#include <QSettings>
#include "DapAbstractCommand.h"
#include <QRegularExpression>

class DapGetTransactionsHistoryCommand : public DapAbstractCommand
{
public:
    static const QString TIME;
    static const QString AMOUNT;
    static const QString TOKEN;
    static const QString ADDRESS;
    static const QString HASH;
    static const QString STATE;
    static const QString INCOME_TYPE;

    enum State {MEMPOOL,SUCCESSFUL,CENCELED};

    /// Overloaded constructor.
    /// @param asServiceName Service name.
    /// @param parent Parent.
    /// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
    /// @param asCliPath The path to cli nodes.
    DapGetTransactionsHistoryCommand(const QString &asServicename, QObject *parent = nullptr, const QString &asCliPath = QString());

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
private:
    static void parseTxHistoryResultAndAdd(const QString &a_result, QVariantMap &a_allTransactions);

    static const QStringList month;
    static QString convertTimeFromHistory(const QString& a_string);
};
