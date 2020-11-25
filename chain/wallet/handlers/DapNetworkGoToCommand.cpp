#include "DapNetworkGoToCommand.h"

#include <QRegularExpression>

const QString DapNetworkGoToCommand::NETWORK_NAME = "name";
const QString DapNetworkGoToCommand::STATE = "state";
const QString DapNetworkGoToCommand::TARGET_STATE = "targetState";

/// Overloaded constructor.
/// @param asServiceName Service name.
/// @param parent Parent.
/// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
DapNetworkGoToCommand::DapNetworkGoToCommand(const QString &asServicename, QObject *parent, const QString &asCliPath)
    : DapAbstractCommand(asServicename, parent, asCliPath)
{

}

/// Send a response to the client.
/// @details Performed on the service side.
/// @param arg1...arg10 Parameters.
/// @return Reply to client.
QVariant DapNetworkGoToCommand::respondToClient(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3,
                                              const QVariant &arg4, const QVariant &arg5, const QVariant &arg6,
                                              const QVariant &arg7, const QVariant &arg8, const QVariant &arg9,
                                              const QVariant &arg10)
{
    Q_UNUSED(arg3)
    Q_UNUSED(arg4)
    Q_UNUSED(arg5)
    Q_UNUSED(arg5)
    Q_UNUSED(arg6)
    Q_UNUSED(arg7)
    Q_UNUSED(arg8)
    Q_UNUSED(arg9)
    Q_UNUSED(arg10)

    QProcess process;
    QString command(QString("%1 net -net %2 go %3").arg(m_sCliPath).arg(arg1.toString()));

    QString target = arg2.toBool() ? "online" : "offline";
    command = command.arg(target);

    process.start(command);
    process.waitForFinished(-1);
    QString result = QString::fromLatin1(process.readAll());

    QRegularExpression rx(R"***(Network "(\S+)" go from state (\S+) to (\S+))***");
    QRegularExpressionMatch match = rx.match(result);
    if (!match.hasMatch()) {
        return {};
    }

    return QJsonObject{
        {NETWORK_NAME, match.captured(1)},
        {STATE       , match.captured(2)},
        {TARGET_STATE, match.captured(3)}
    };
}
