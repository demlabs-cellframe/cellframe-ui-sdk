#include "DapGetNetworkStatusCommand.h"

#include <QRegularExpression>

/// Overloaded constructor.
/// @param asServiceName Service name.
/// @param parent Parent.
/// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
/// @param asCliPath The path to cli nodes.
DapGetNetworkStatusCommand::DapGetNetworkStatusCommand(const QString &asServicename, QObject *parent, const QString &asCliPath)
    : DapAbstractCommand(asServicename, parent, asCliPath)
{

}

/// Send a response to the client.
/// @details Performed on the service side.
/// @param arg1...arg10 Parameters.
/// @return Reply to client.
QVariant DapGetNetworkStatusCommand::respondToClient(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, const QVariant &arg10)
{
    Q_UNUSED(arg2)
    Q_UNUSED(arg3)
    Q_UNUSED(arg4)
    Q_UNUSED(arg5)
    Q_UNUSED(arg6)
    Q_UNUSED(arg7)
    Q_UNUSED(arg8)
    Q_UNUSED(arg9)
    Q_UNUSED(arg10)

    QString network(arg1.toString());

    QProcess process;
    QString command(QString("%1 net -net %2 get status").arg(m_sCliPath).arg(arg1.toString()));
    process.start(command);
    process.waitForFinished(-1);
    QString result = QString::fromLatin1(process.readAll());

    QRegularExpression rx(R"(Network "\S+" has state (\S+) \(target state (\S*)\), cur node address ([A-F0-9]{4}::[A-F0-9]{4}::[A-F0-9]{4}::[A-F0-9]{4}))");
    QRegularExpressionMatch match = rx.match(result);
    if (!match.hasMatch()) {
        return {};
    }

    QJsonObject returnValue({
                                {"name"      , network},
                                {"state"        , match.captured(1)},
                                {"targetState"  , match.captured(2)},
                                {"nodeAddress"  , match.captured(3)}
                            });

    return returnValue;
}
