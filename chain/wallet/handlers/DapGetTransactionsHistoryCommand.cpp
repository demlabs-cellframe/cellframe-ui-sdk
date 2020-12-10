#include "DapGetTransactionsHistoryCommand.h"

const QString DapGetTransactionsHistoryCommand::TIME = "time";
const QString DapGetTransactionsHistoryCommand::AMOUNT = "amount";
const QString DapGetTransactionsHistoryCommand::TOKEN = "tokenName";
const QString DapGetTransactionsHistoryCommand::ADDRESS = "address";
const QString DapGetTransactionsHistoryCommand::HASH = "hash";
const QString DapGetTransactionsHistoryCommand::STATE = "state";
const QString DapGetTransactionsHistoryCommand::INCOME_TYPE = "income";


const QStringList DapGetTransactionsHistoryCommand::month {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

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

    QVariantMap resultMap;

    QString networkName = arg2.canConvert<QStringList>() ? arg2.toStringList()[0] : arg2.toString();
    QString walletName = arg1.toString();

    //------------------- Successful: -------------------

    QString command("%1 tx_history -w %2 -net %3 -chain %4");
    command = command.arg(m_sCliPath);
    command = command.arg(walletName);
    command = command.arg(networkName);

    QProcess processCreate;
    for (QString chain: {"zerochain", "bronze"})
    {
        processCreate.start(command.arg(chain));

        processCreate.waitForFinished(-1);
        DapGetTransactionsHistoryCommand::parseTxHistoryResultAndAdd(QString::fromLatin1(processCreate.readAll()), resultMap);
    }

    //------------------- Nempool: -------------------

    processCreate.start(QString("%1 mempool_list -net %2")
                        .arg(m_sCliPath)
                        .arg(networkName));

    processCreate.waitForFinished(-1);

    QSettings settings(DAP_BRAND + QString(".ini"), QSettings::IniFormat);
    settings.beginGroup(walletName);
    QStringList hashList = settings.childGroups();
    settings.endGroup();

    if (hashList.isEmpty())
        return QJsonObject::fromVariantMap(resultMap); // No sense for continue

    QStringList resultMempoolList = QString(processCreate.readAll()).split("\n");

    auto settingsKey = QString("%1/%2/%3").arg(walletName);
    QString hashSettingsKey;
    for(auto &line: resultMempoolList)
    {
        if(line.isEmpty() || line == "\r")
            continue;

        QRegExp rxMempool("data_hash=0x(\\w+) ts_create=([A-Za-z]{3} [A-Za-z]{3} [0-9\\s]{0,2} [0-9\\:]{8} [0-9]{4})");
        rxMempool.indexIn(line);
        if (rxMempool.cap(0).isEmpty())
            continue;

        auto hash = rxMempool.cap(1);

        hashSettingsKey = settingsKey.arg(hash);

        if (!settings.contains(hashSettingsKey.arg(AMOUNT)))
            continue; //tx isn't our's

        QString txTime = convertTimeFromHistory(rxMempool.cap(2));
        if (!settings.contains(hashSettingsKey.arg(TIME)))
            settings.setValue(hashSettingsKey.arg(TIME), txTime);

        resultMap.insert(hash, QJsonObject {
            {TIME       , txTime},
            {AMOUNT     , settings.value(hashSettingsKey.arg(AMOUNT)).toString()},
            {TOKEN      , settings.value(hashSettingsKey.arg(TOKEN)).toString()},
            {ADDRESS    , settings.value(hashSettingsKey.arg(ADDRESS)).toString()},
            {INCOME_TYPE, false},
            {STATE      , State::MEMPOOL}
        });
    }

    //------------------- Canceled: -------------------
    for(auto &hash: hashList)
    {
        if(!resultMap.contains(hash))
        {
            hashSettingsKey = settingsKey.arg(hash);

            resultMap.insert(hash, QJsonObject{
                {TIME   , settings.value(hashSettingsKey.arg(TIME)).toString()},
                {AMOUNT , settings.value(hashSettingsKey.arg(AMOUNT)).toString()},
                {TOKEN  , settings.value(hashSettingsKey.arg(TOKEN)).toString()},
                {ADDRESS, settings.value(hashSettingsKey.arg(ADDRESS)).toString()},
                {STATE  , State::CENCELED}
            });
        }
    }

    return QJsonObject::fromVariantMap(resultMap);
}

void DapGetTransactionsHistoryCommand::parseTxHistoryResultAndAdd(const QString &a_result, QVariantMap &a_allTransactions)
{
    QStringList resultList = a_result.split("tx hash ");
    for(auto curTx:resultList)
    {
        if(curTx.contains("history") || curTx.isEmpty())
            continue;

        QRegExp rxHash("^0x(\\w+)");
        rxHash.indexIn(curTx);
        auto hash = rxHash.cap(1);
        if(hash.isEmpty())
            continue; //can't be empty hash

        QJsonObject resultObj{{TIME, convertTimeFromHistory(curTx)}};

        if(!curTx.contains("in send"))
        {
            QRegExp rxSendRecv("(recv|send) ([0-9]*) ([A-Z]*) (from|to) ([A-Za-z0-9]*)");
            if (rxSendRecv.indexIn(curTx) != -1)
            {                   
                auto type = rxSendRecv.cap(1);

                resultObj.insert(INCOME_TYPE, type == "recv");
                resultObj.insert(AMOUNT,rxSendRecv.cap(2));
                resultObj.insert(TOKEN,rxSendRecv.cap(3));
                resultObj.insert(ADDRESS,rxSendRecv.cap(5));
            }
            else if(curTx.contains("emit"))
            {
                QRegExp rxEmit("(emit) ([0-9]*) ([A-Z]*)");
                rxEmit.indexIn(curTx);
                resultObj.insert(INCOME_TYPE, true);
                resultObj.insert(AMOUNT, rxEmit.cap(2));
                resultObj.insert(TOKEN, rxEmit.cap(3));
            }
        }

        resultObj.insert(STATE, State::SUCCESSFUL);
        a_allTransactions.insert(hash, resultObj);
    }
}

QString DapGetTransactionsHistoryCommand::convertTimeFromHistory(const QString& a_string)
{
    QRegExp rxTime("([A-Za-z]{3}) ([A-Za-z]{3}) ([0-9\\s]+) ([0-9\\:]{8}) ([0-9]{4})");
    rxTime.indexIn(a_string);

    if(!rxTime.cap(0).isEmpty())
    {
        int month = 0;
        for(int index = 0; index < DapGetTransactionsHistoryCommand::month.count();index++)
        {
            if(rxTime.cap(2) == DapGetTransactionsHistoryCommand::month.at(index))
            {
                month = index+1;
            }
        }
        QDate date(rxTime.cap(5).toInt(),month,rxTime.cap(3).toInt());
        QTime time = QTime::fromString(QString("%1").arg(rxTime.cap(4)),"hh:mm:ss");

        return QDateTime(date,time).toString();
    }
    else
    {
        return "";
    }

}
