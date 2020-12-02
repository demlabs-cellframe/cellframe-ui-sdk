#include "DapCreateTransactionCommand.h"

const QString DapCreateTransactionCommand::SUCCESS = "success";
const QString DapCreateTransactionCommand::ERROR_MESSAGE = "errorMessage";

const QString DapCreateTransactionCommand::WALLET_NAME = "walletName";
const QString DapCreateTransactionCommand::NETWORK = "network";
const QString DapCreateTransactionCommand::RECIEVER_ADDRESS = "recieverAddress";
const QString DapCreateTransactionCommand::AMOUNT = "amount";
const QString DapCreateTransactionCommand::TOKEN = "token";



/// Overloaded constructor.
/// @param asServiceName Service name.
/// @param parent Parent.
/// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
/// @param asCliPath The path to cli nodes.
DapCreateTransactionCommand::DapCreateTransactionCommand(const QString &asServicename, QObject *parent, const QString &asCliPath)
    : DapAbstractCommand(asServicename, parent, asCliPath)
{

}

/// Send a response to the client.
/// @details Performed on the service side.
/// @param arg1 Network.
/// @param arg2 Chain.
/// @param arg3 Wallet sender.
/// @param arg4 Recipient's wallet address.
/// @param arg5 Token.
/// @param arg6 Transfer amount.
/// @return Reply to client.
QVariant DapCreateTransactionCommand::respondToClient(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, const QVariant &arg10)
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

    QVariantMap dataMap = arg1.toMap();

    QString command = QString("%1 tx_create -net %2 -chain bronze -from_wallet %3 -to_addr %4 -token %5 -value %6").arg(m_sCliPath);
    command = command.arg(dataMap.value(NETWORK).toString());
    command = command.arg(dataMap.value(WALLET_NAME).toString());
    command = command.arg(dataMap.value(RECIEVER_ADDRESS).toString());
    command = command.arg(dataMap.value(TOKEN).toString());
    command = command.arg(dataMap.value(AMOUNT).toLongLong());

    QProcess processCreate;
    processCreate.start(command);
    processCreate.waitForFinished(-1);

    QJsonObject resultObj;
    QString result = QString::fromLatin1(processCreate.readAll());
    QRegExp rx("transfer=(\\w+)");
    rx.indexIn(result, 0);

    if(rx.cap(1) == "Ok")
    {
        QRegExp rxHash("tx_hash=(\\w+)");
        rxHash.indexIn(result, 0);

        QSettings settings(DAP_BRAND + QString(".ini"), QSettings::IniFormat);
        settings.beginGroup(dataMap.value(WALLET_NAME).toString());
            settings.beginGroup(rxHash.cap(1));
                settings.setValue(DapGetTransactionsHistoryCommand::TIME,       "");
                settings.setValue(DapGetTransactionsHistoryCommand::AMOUNT,     "-" + dataMap.value(AMOUNT).toString());
                settings.setValue(DapGetTransactionsHistoryCommand::TOKEN,      dataMap.value(TOKEN).toString());
                settings.setValue(DapGetTransactionsHistoryCommand::ADDRESS,    dataMap.value(RECIEVER_ADDRESS).toString());
            settings.endGroup();
        settings.endGroup();

        resultObj.insert(SUCCESS,true);
    }
    else
    {
        resultObj.insert(SUCCESS,false);

        QRegExp rxError("not enough funds for transfer");
        rxError.indexIn(result, 0);
        if(!rxError.cap(0).isEmpty())
            resultObj.insert(ERROR_MESSAGE,DapErrors::Error::NOT_ENOUGH_FUNDS_FOR_TRANSFER);
        else
             resultObj.insert(ERROR_MESSAGE,DapErrors::Error::UNKNOWN_ERROR);
    }
    return resultObj;
}
