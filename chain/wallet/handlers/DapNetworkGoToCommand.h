/****************************************************************************
**
** This file is part of the libdap-qt-ui-chain-wallet library.
** 
** The class implements the functionality of creating a new wallet.
**
****************************************************************************/

#ifndef DAPNETWORKGOTOCOMMAND_H
#define DAPNETWORKGOTOCOMMAND_H

#include <QProcess>
#include <QString>

#include "DapAbstractCommand.h"
#include "DapNetwork.h"


class DapNetworkGoToCommand : public DapAbstractCommand
{
public:
    /// Overloaded constructor.
    /// @param asServiceName Service name.
    /// @param parent Parent.
    /// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
    explicit DapNetworkGoToCommand(const QString &asServicename, QObject *parent, const QString &asCliPath = QString());

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

#endif // DAPNETWORKGOTOCOMMAND_H
