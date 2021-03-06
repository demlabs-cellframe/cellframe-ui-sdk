#ifndef DAPGETNETWORKSTATUSCOMMAND_H
#define DAPGETNETWORKSTATUSCOMMAND_H

#include <QProcess>

#include "DapAbstractCommand.h"

class DapGetNetworkStatusCommand : public DapAbstractCommand
{
public:
    
    static const QString NAME;
    static const QString STATE;
    static const QString TARGET_STATE;
    static const QString ACTIVE_LINKS_COUNT;
    static const QString LINKS_COUNT;
    static const QString NODE_ADDRESS;
    
    /// Overloaded constructor.
    /// @param asServiceName Service name.
    /// @param parent Parent.
    /// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
    /// @param asCliPath The path to cli nodes.
    DapGetNetworkStatusCommand(const QString &asServicename, QObject *parent = nullptr, const QString &asCliPath = QString());

public slots:
    /// Send a response to the client.
    /// @details Performed on the service side.
    /// @param arg1...arg10 Parameters.
    /// @return Reply to client.
    QVariant respondToClient(const QVariant &arg1 = QVariant(), const QVariant &arg2 = QVariant(),
                             const QVariant &arg3 = QVariant(), const QVariant &arg4 = QVariant(),
                             const QVariant &arg5 = QVariant(), const QVariant &arg6 = QVariant(),
                             const QVariant &arg7 = QVariant(), const QVariant &arg8 = QVariant(),
                             const QVariant &arg9 = QVariant(), const QVariant &arg10 = QVariant()) override;
};

#endif // DAPGETNETWORKSTATUSCOMMAND_H
