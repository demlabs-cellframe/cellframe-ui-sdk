#include "DapGetWalletInfoCommand.h"

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
    Q_UNUSED(arg1)
    Q_UNUSED(arg2)
    Q_UNUSED(arg3)
    Q_UNUSED(arg4)
    Q_UNUSED(arg5)
    Q_UNUSED(arg6)
    Q_UNUSED(arg7)
    Q_UNUSED(arg8)
    Q_UNUSED(arg9)
    Q_UNUSED(arg10)

    QStringList list;
    QProcess processGetNetworks;
    processGetNetworks.start(QString("%1 net list").arg(m_sCliPath));
    processGetNetworks.waitForFinished(-1);
    QString result = QString::fromLatin1(processGetNetworks.readAll());
    result.remove(' ');
    if(!(result.isEmpty() || result.isNull() || result.contains('\'')))
    {
        list = result.remove("\n").remove("\r").split(":").at(1).split(",");
    }

    DapWallet wallet;
    wallet.setName(arg1.toString());
    auto begin = list.begin();
    auto end = list.end();
    for(; begin != end; ++begin)
    {

        wallet.addNetwork(*begin);

        QProcess processGetTokkens;
        processGetTokkens.start(QString("%1 wallet info -w %2 -net %3")
                            .arg(m_sCliPath)
                            .arg(wallet.getName())
                            .arg(*begin));

        processGetTokkens.waitForFinished(-1);
        QByteArray result_tokens = processGetTokkens.readAll();
        QRegExp regex("wallet: (.+)\\s+addr:\\s+(.+)\\s+(balance)|(\\d+.\\d+)\\s\\((\\d+)\\)\\s(\\w+)");

        int pos = 0;
        DapWalletToken *token {nullptr};
        while((pos = regex.indexIn(result_tokens, pos)) != -1)
        {

            if(!regex.cap(2).isEmpty())
            {
                wallet.addAddress(regex.cap(2), *begin);
            }
            else
            {
                token = new DapWalletToken();
                token->setName(regex.cap(6).trimmed());
                token->setBalance(regex.cap(4).toDouble());
                QString str = regex.cap(5);
                token->setEmission(regex.cap(5).toULongLong());
                token->setNetwork(*begin);
                wallet.addToken(token);
            }

            pos += regex.matchedLength();
        }
    }

    QByteArray datas;
    QDataStream out(&datas, QIODevice::WriteOnly);
    out << wallet;

    return QJsonValue::fromVariant(datas.toHex());
}


/// Reply from service.
/// @details Performed on the service side.
/// @return Service reply.
QVariant DapGetWalletInfoCommand::replyFromService()
{
    DapRpcServiceReply *reply = static_cast<DapRpcServiceReply *>(sender());

    emit serviceResponded(reply->response().toJsonValue().toVariant().toByteArray());

    return reply->response().toJsonValue().toVariant();
}

