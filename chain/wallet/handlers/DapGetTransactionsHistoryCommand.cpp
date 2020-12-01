#include "DapGetTransactionsHistoryCommand.h"

const QString DapGetTransactionsHistoryCommand::TIME = "time";
const QString DapGetTransactionsHistoryCommand::ACTION = "action";
const QString DapGetTransactionsHistoryCommand::AMOUNT = "amount";
const QString DapGetTransactionsHistoryCommand::TOKEN = "tokenName";
const QString DapGetTransactionsHistoryCommand::ADDRESS = "address";
const QString DapGetTransactionsHistoryCommand::HASH = "hash";
const QString DapGetTransactionsHistoryCommand::STATE_TRANSACTION = "stateTransaction";


/// Overloaded constructor.
/// @param asServiceName Service name.
/// @param parent Parent.
/// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
/// @param asCliPath The path to cli nodes.
DapGetTransactionsHistoryCommand::DapGetTransactionsHistoryCommand(const QString &asServicename, QObject *parent, const QString &asCliPath)
    : DapAbstractCommand(asServicename, parent, asCliPath)
{

}

/// Send a response to the client.
/// @details Performed on the service side.
/// @param arg1...arg10 Parameters.
/// @return Reply to client.
QVariant DapGetTransactionsHistoryCommand::respondToClient(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3,
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

    QJsonArray resultArray;

    QString networkName = arg2.canConvert<QStringList>() ? arg2.toStringList()[0] : arg2.toString();

    QString command("%1 tx_history -w %2 -net %3 -chain %4");
    command = command.arg(m_sCliPath);
    command = command.arg(arg1.toString());
    command = command.arg(networkName);

    QProcess processCreate;
    for (QString chain: {"zerochain", "bronze"})
    {
        processCreate.start(command.arg(chain));

        processCreate.waitForFinished(-1);
        addToTransactionArray(resultArray, QString::fromLatin1(processCreate.readAll()));
    }

    processCreate.start(QString("%1 mempool_list -net %2")
                        .arg(m_sCliPath)
                        .arg(networkName));



    processCreate.waitForFinished(-1);
    //resultList.clear();
    QStringList resultMempoolList = QString(processCreate.readAll()).split("\n");

    QJsonArray mempoolArray;
    for(auto line:resultMempoolList)
    {
        if(!line.isEmpty() && line != "\r")
        {
            QRegExp rxMempool("data_hash=(\\w+) ts_create=([A-Za-z]{3} [A-Za-z]{3} [0-9]{2} [0-9\\:]{8} [0-9]{4})");
            rxMempool.indexIn(line);
            if(!rxMempool.cap(0).isEmpty())
            {

                QJsonObject tmpResult;
                tmpResult.insert(HASH, rxMempool.cap(1));
                tmpResult.insert(TIME, convertTimeFromHistory(rxMempool.cap(2)));
                mempoolArray.append(tmpResult);
            }
        }
    }
    if(!mempoolArray.isEmpty())
        DapSaveTransaction::creatLocalHistory(resultArray,mempoolArray);

    return resultArray;
}

void DapGetTransactionsHistoryCommand::addToTransactionArray(QJsonArray &a_array, const QString &a_string)
{
    QStringList resultList = a_string.split("tx hash ");
    for(auto curTx:resultList)
    {
        if(curTx.contains("history") || curTx.isEmpty())
            continue;

        QJsonObject resultObj;

        QRegExp rxHash("^(\\w+)");
        rxHash.indexIn(curTx);
        if(!rxHash.cap(1).isEmpty())
            resultObj.insert(HASH,rxHash.cap(1));
        else
            resultObj.insert(HASH,"");

        resultObj.insert(TIME, convertTimeFromHistory(curTx));


        if(!curTx.contains("in recv") && !curTx.contains("in send"))
        {
            if(curTx.contains("recv") || curTx.contains("send") )
            {
                QRegExp rxSendRecv("(recv|send) ([0-9]{0,}) ([A-Z]{0,}) (from|to) ([A-Za-z0-9]{0,})");
                rxSendRecv.indexIn(curTx);
                if(rxSendRecv.cap(2) == "send")
                    resultObj.insert(AMOUNT,"-"+rxSendRecv.cap(2));
                resultObj.insert(AMOUNT,rxSendRecv.cap(2));
                resultObj.insert(TOKEN,rxSendRecv.cap(3));
                resultObj.insert(ADDRESS,rxSendRecv.cap(5));

            }
            else if(curTx.contains("emit"))
            {
                QRegExp rxEmit("(emit) ([0-9]{0,}) ([A-Z]{0,})");
                rxEmit.indexIn(curTx);
                resultObj.insert(AMOUNT, rxEmit.cap(2));
                resultObj.insert(TOKEN, rxEmit.cap(3));
            }
        }


        //  Requires clarification
        //        if(iter.contains("in send"))
        //        {
        //            QRegExp rxSend("(in send) ([0-9]{0,}) ([A-Z]{0,}) (from) ([A-Za-z0-9]{0,})\\n to ([A-Za-z0-9]{0,})");
        //            rxSend.indexIn(iter);
        //            resultObj.insert(TransactionAction,rxSend.cap(1));
        //            resultObj.insert(TransactionPrice,rxSend.cap(2));
        //            resultObj.insert(TransactionTokenName,rxSend.cap(3));
        //            resultObj.insert(TransactionSenderAddress,rxSend.cap(5));
        //            resultObj.insert(TransactionRecipientAddress,rxSend.cap(6));
        //        }
        resultObj.insert(STATE_TRANSACTION, StateTrasaction::SUCCESSFUL);
        a_array.append(resultObj);
    }
}

QString DapGetTransactionsHistoryCommand::convertTimeFromHistory(const QString& a_string)
{
    QRegExp rxTime("([A-Za-z]{3}) ([A-Za-z]{3}) ([0-9]{2}) ([0-9\\:]{8}) ([0-9]{4})");
    rxTime.indexIn(a_string);

    if(!rxTime.cap(0).isEmpty())
    {
        int month = 0;
        for(int index = 0; index < m_month.count();index++)
        {
            if(rxTime.cap(2) == m_month.at(index))
            {
                month = index+1;
            }
        }
        QDate date(rxTime.cap(5).toInt(),month,rxTime.cap(3).toInt());
        QTime time = QTime::fromString(QString("%1").arg(rxTime.cap(4)),"hh:mm:ss");

        return QDateTime(date,time).toString();
        //resultObj.insert(TIME, QDateTime(date,time).toString());
    }
    else
    {
        return "";
       // resultObj.insert(TIME, "");
    }

    return QString();
}
