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
    QJsonObject networks;

    QStringList networkLists;
    if (!arg2.canConvert<QStringList>())
        networkLists.append(arg2.toString());
    else
        networkLists = arg2.toStringList();


    QProcess process;
    QString command(QString("%1 wallet info -w %2 -net %3")
                    .arg(m_sCliPath)
                    .arg(walletName));


    for (const QString& network: networkLists)
    {
        QString networkCommand = command.arg(network);
        process.start(networkCommand);

        process.waitForFinished(-1);
        QString result(process.readAll());

        QRegularExpression regex(R"(wallet: (\S+)\saddr: (\S+)\sbalance:)");

        QRegularExpressionMatch match = regex.match(result);
        if (!match.hasMatch()) {
            return {};
        }

        QRegularExpression balanceRegex(R"((\d+.\d+) \((\d+)\) (\w+))");
        QRegularExpressionMatchIterator matchIt = balanceRegex.globalMatch(result);

        QString address = match.captured(2);

        QJsonObject balance;
        while (matchIt.hasNext())
        {
            QRegularExpressionMatch match = matchIt.next();
            QString amount = match.captured(2);
            QString token = match.captured(3);
            balance.insert(token, amount);
        }
        QJsonObject networkInfo{
            {ADDRESS, address},
            {BALANCE, balance}
        };
        networks.insert(network, networkInfo);
    }


    QJsonObject returnValue({
                                {WALLET_NAME  , walletName },
                                {NETWORKS_INFO, networks   }
                            });



    return returnValue;
}
