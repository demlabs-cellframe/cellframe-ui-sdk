/****************************************************************************
**
** This file is part of the libdap-qt-ui-chain-wallet library.
** 
** The class implements the functionality of creating a new wallet.
**
****************************************************************************/

#ifndef DAPADDWALLETCOMMAND_H
#define DAPADDWALLETCOMMAND_H

#include <QProcess>
#include <QString>

#include "DapAbstractCommand.h"

class DapAddWalletCommand : public DapAbstractCommand
{
public:

    static const QString SUCCESS;
    static const QString MESSAGE;
    static const QString WALLET_NAME;

    static const QString SIGNATURE_TYPE;
    static const QString USE_EXISTING;

    /// Overloaded constructor.
    /// @param asServiceName Service name.
    /// @param parent Parent.
    /// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
    explicit DapAddWalletCommand(const QString &asServicename, QObject *parent = nullptr);

public slots:
    /// Send a response to the client.
    /// @details Performed on the service side.
    /// @param arg1...arg10 Parameters.
    /// @return Reply to client.
    QVariant respondToClient(const QVariant &arg1 = QVariant(), const QVariant &arg2 = QVariant(),    //original
                             const QVariant &arg3 = QVariant(), const QVariant &arg4 = QVariant(),
                             const QVariant &arg5 = QVariant(), const QVariant &arg6 = QVariant(),
                             const QVariant &arg7 = QVariant(), const QVariant &arg8 = QVariant(),
                             const QVariant &arg9 = QVariant(), const QVariant &arg10 = QVariant()) override;




};

#endif // DAPADDWALLETCOMMAND_H
