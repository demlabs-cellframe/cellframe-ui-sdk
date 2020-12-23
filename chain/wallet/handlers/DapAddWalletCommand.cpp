#include "DapAddWalletCommand.h"

const QString DapAddWalletCommand::SUCCESS = "success";
const QString DapAddWalletCommand::MESSAGE = "message";
const QString DapAddWalletCommand::WALLET_NAME = "walletName";

const QString DapAddWalletCommand::SIGNATURE_TYPE = "signatureType";
const QString DapAddWalletCommand::USE_EXISTING = "useExisting";



/// Overloaded constructor.
/// @param asServiceName Service name.
/// @param parent Parent.
/// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
DapAddWalletCommand::DapAddWalletCommand(const QString &asServicename, QObject *parent)
    : DapAbstractCommand(asServicename, parent)
{

}

/// Send a response to the client.
/// @details Performed on the service side.
/// @param arg1...arg10 Parameters.
/// @return Reply to client.
QVariant DapAddWalletCommand::respondToClient(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3,
                                              const QVariant &arg4, const QVariant &arg5, const QVariant &arg6,
                                              const QVariant &arg7, const QVariant &arg8, const QVariant &arg9,
                                              const QVariant &arg10)
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

    QJsonObject resultObj;
    QProcess process;

    auto requestData = arg1.toMap();

    auto command = QString("%1 wallet new -w %2 -sign %3").arg(CLI_PATH);

    command = command.arg(requestData.value(WALLET_NAME).toString());
    command = command.arg(requestData.value(SIGNATURE_TYPE).toString());
    if (requestData.value(USE_EXISTING).toBool())
        command += " -force";

    process.start(command);
    process.waitForFinished(-1);
    QString result = QString::fromLatin1(process.readAll());
    if(result.contains("successfully created"))
    {
        resultObj.insert(SUCCESS,QJsonValue(true));
        resultObj.insert(MESSAGE,QJsonValue("Wallet successfully created"));
        resultObj.insert(WALLET_NAME,QJsonValue(requestData.value(WALLET_NAME).toString()));
    }
    else
    {
        resultObj.insert(SUCCESS,QJsonValue(false));
        resultObj.insert(MESSAGE,QJsonValue("Creating wallet error"));
    }
    return resultObj;
}
