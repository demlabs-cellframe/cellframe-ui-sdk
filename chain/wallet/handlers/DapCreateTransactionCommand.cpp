#include "DapCreateTransactionCommand.h"

const QString DapCreateTransactionCommand::SUCCESS = "success";
const QString DapCreateTransactionCommand::ERROR_MESSAGE = "errorMessage";

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
    Q_UNUSED(arg7)
    Q_UNUSED(arg8)
    Q_UNUSED(arg9)
    Q_UNUSED(arg10)

    QProcess processCreate;
    processCreate.start(QString("%1 tx_create -net %2 -chain %3 -from_wallet %4 -to_addr %5 -token %6 -value %7")
                  .arg(m_sCliPath)
                  .arg(arg1.toString())
                  .arg(arg2.toString())
                  .arg(arg3.toString())
                  .arg(arg4.toString())
                  .arg(arg5.toString())
                  .arg(arg6.toString()));

    processCreate.waitForFinished(-1);

    QJsonObject resultObj;
    QString result = QString::fromLatin1(processCreate.readAll());
    QRegExp rx("transfer=(\\w+)");
    rx.indexIn(result, 0);

    if(rx.cap(1) == "Ok")
    {
        resultObj.insert(SUCCESS,true);
    }
    else
    {
        QRegExp rxError("not enough funds for transfer");
        rxError.indexIn(result, 0);
        if(!rxError.cap(0).isEmpty())
            resultObj.insert(ERROR_MESSAGE,DapErrors::Error::NOT_ENOUGH_FOUNDS_FOR_TRANSFER);
        else
             resultObj.insert(ERROR_MESSAGE,DapErrors::Error::UNKNOWN_ERROR);
        resultObj.insert(SUCCESS,false);

    }
    return resultObj;
}
