#include "DapGetWalletInfoCommand.h"


const QString DapGetWalletInfoCommand::WALLET_NAME = "walletName";
const QString DapGetWalletInfoCommand::NETWORKS_INFO = "networksInfo";
const QString DapGetWalletInfoCommand::ADDRESS = "address";
const QString DapGetWalletInfoCommand::BALANCE = "balance";


/// Overloaded constructor.
/// @param asServiceName Service name.
/// @param parent Parent.
/// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
/// @param asCliPath The path to cli nodes.
DapGetWalletInfoCommand::DapGetWalletInfoCommand(const QString &asServicename, QObject *parent, const QString &asCliPath)
    : DapAbstractCommand(asServicename, parent, asCliPath)
{

}

/// Send a response to the client.
/// @details Performed on the service side.
/// @param arg1...arg10 Parameters.
/// @return Reply to client.
QVariant DapGetWalletInfoCommand::respondToClient(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3,
                                              const QVariant &arg4, const QVariant &arg5, const QVariant &arg6,
                                              const QVariant &arg7, const QVariant &arg8, const QVariant &arg9,
                                              const QVariant &arg10)
{
    Q_UNUSED(arg3)
    Q_UNUSED(arg4)
    Q_UNUSED(arg5)
    Q_UNUSED(arg6)
    Q_UNUSED(arg7)
    Q_UNUSED(arg8)
    Q_UNUSED(arg9)
    Q_UNUSED(arg10)

    QString walletName = arg1.toString();

    QStringList networkLists;
    if (!arg2.canConvert<QStringList>())
        networkLists.append(arg2.toString());
    else
        networkLists = arg2.toStringList();


    QProcess process;
    QString command(QString("%1 wallet info -w %2 -net %3")
                    .arg(m_sCliPath)
                    .arg(walletName));

    QJsonObject returnValue;
    QJsonObject networks;
    for (const QString& network: networkLists)
    {
        QString networkCommand = command.arg(network);
        process.start(networkCommand);

        process.waitForFinished(-1);
        QString result(process.readAll());


        //Name:
        QRegularExpression regex(R"(^wallet: (\S+)\naddr: (\S+)\nnetwork: (\S+)\nbalance:)");
        QRegularExpressionMatch match = regex.match(result);
        if (!match.hasMatch()) {
            qWarning() << "Can't parse result";
            return {};
        }
        returnValue.insert(WALLET_NAME, match.captured(1));

        QString networkName = match.captured(3);
        QJsonObject networkInfo {{
            ADDRESS, match.captured(2)
        }};

        //Balance:
        QRegularExpression balanceRegex(R"((\d+.\d+) \((\d+)\) (\w+))");
        QRegularExpressionMatchIterator matchIt = balanceRegex.globalMatch(result);

        QJsonObject balance;
        while (matchIt.hasNext())
        {
            QRegularExpressionMatch match = matchIt.next();
            QString amount = match.captured(2);
            QString token = match.captured(3);
            balance.insert(token, amount);
        }

        networkInfo.insert(BALANCE, balance);
        networks.insert(networkName, networkInfo);
    }
    returnValue.insert(NETWORKS_INFO, networks);
    return returnValue;
}
