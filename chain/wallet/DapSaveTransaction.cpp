#include "DapSaveTransaction.h"

const QString DapSaveTransaction::TRANSACRIONS_COUNT = "Transactions";

DapSaveTransaction::DapSaveTransaction()
{
}

QJsonArray DapSaveTransaction::readFomFile()
{
    QSettings settings(DAP_BRAND + QString(".ini"), QSettings::IniFormat);
    QJsonArray resulArray;
    int count = settings.value(TRANSACRIONS_COUNT).toInt();
    for(int i = 0; i<count ;++i)
    {
        QJsonObject tmpJsonObj;
        settings.beginGroup(QString::number(i));
        tmpJsonObj.insert(DapGetTransactionsHistoryCommand::HASH,       settings.value(DapGetTransactionsHistoryCommand::HASH).toString());
        tmpJsonObj.insert(DapGetTransactionsHistoryCommand::TIME,       settings.value(DapGetTransactionsHistoryCommand::TIME).toString());
        tmpJsonObj.insert(DapGetTransactionsHistoryCommand::AMOUNT,     settings.value(DapGetTransactionsHistoryCommand::AMOUNT).toString());
        tmpJsonObj.insert(DapGetTransactionsHistoryCommand::TOKEN,      settings.value(DapGetTransactionsHistoryCommand::TOKEN).toString());
        tmpJsonObj.insert(DapGetTransactionsHistoryCommand::ADDRESS,    settings.value(DapGetTransactionsHistoryCommand::ADDRESS).toString());

        settings.endGroup();

        resulArray.append(tmpJsonObj);
    }
    return resulArray;
}
void DapSaveTransaction::saveToFileFromCreat(QJsonArray &a_array)
{
    QSettings settings(DAP_BRAND + QString(".ini"), QSettings::IniFormat);
    QJsonArray tmpArray(readFomFile());
    for(auto transactionItem: a_array)
    {
        tmpArray.append(transactionItem.toObject());
    }
    int count = tmpArray.count();
    settings.setValue(TRANSACRIONS_COUNT,count);
    for(int i = 0; i<count; ++i)
    {
        settings.beginGroup(QString::number(i));
        settings.setValue(DapGetTransactionsHistoryCommand::HASH,       tmpArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::HASH).toString());
        settings.setValue(DapGetTransactionsHistoryCommand::TIME,       tmpArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::TIME).toString());
        settings.setValue(DapGetTransactionsHistoryCommand::AMOUNT,     tmpArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::AMOUNT).toString());
        settings.setValue(DapGetTransactionsHistoryCommand::TOKEN,      tmpArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::TOKEN).toString());
        settings.setValue(DapGetTransactionsHistoryCommand::ADDRESS,    tmpArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::ADDRESS).toString());

        settings.endGroup();
    }
}
void DapSaveTransaction::saveToFile(QJsonArray &a_array)
{

        QSettings settings(DAP_BRAND + QString(".ini"), QSettings::IniFormat);
        int count = a_array.count();
        settings.setValue(TRANSACRIONS_COUNT,count);
        for(int i = 0; i<count; ++i)
        {
            settings.beginGroup(QString::number(i));
            settings.setValue(DapGetTransactionsHistoryCommand::HASH,       a_array.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::HASH).toString());
            settings.setValue(DapGetTransactionsHistoryCommand::TIME,       a_array.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::TIME).toString());
            settings.setValue(DapGetTransactionsHistoryCommand::AMOUNT,     a_array.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::AMOUNT).toString());
            settings.setValue(DapGetTransactionsHistoryCommand::TOKEN,      a_array.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::TOKEN).toString());
            settings.setValue(DapGetTransactionsHistoryCommand::ADDRESS,    a_array.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::ADDRESS).toString());

            settings.endGroup();
        }
}

void DapSaveTransaction::saveTransactionBySpecifyingTime(const QString a_hash, const QString &a_time, const QString &a_amount,
                                                         const QString &a_token, const QString &a_address)
{
 QJsonArray resultArray;

    QJsonObject newTransaction;
    newTransaction.insert(DapGetTransactionsHistoryCommand::HASH,   a_hash);
    newTransaction.insert(DapGetTransactionsHistoryCommand::TIME,   a_time);
    newTransaction.insert(DapGetTransactionsHistoryCommand::AMOUNT, a_amount);
    newTransaction.insert(DapGetTransactionsHistoryCommand::TOKEN,  a_token);
    newTransaction.insert(DapGetTransactionsHistoryCommand::ADDRESS,a_address);
    resultArray.append(newTransaction);
    saveToFileFromCreat(resultArray);

}

void DapSaveTransaction::creatLocalHistory(QJsonArray& a_resultArray, QJsonArray& a_mempoolArray)
{

    QJsonArray settingsArray(readFomFile());
    for(int i=0; i< settingsArray.count();i++)
    {
        for(auto transactionFromMempool: a_mempoolArray)
        {
            if(settingsArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::HASH).toString() ==
                    transactionFromMempool.toVariant().toMap().value(DapGetTransactionsHistoryCommand::HASH).toString())
            {
                QJsonObject object;
                object.insert(DapGetTransactionsHistoryCommand::HASH,               settingsArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::HASH).toString());
                object.insert(DapGetTransactionsHistoryCommand::TIME,               transactionFromMempool.toVariant().toMap().value(DapGetTransactionsHistoryCommand::TIME).toString());
                object.insert(DapGetTransactionsHistoryCommand::AMOUNT,             settingsArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::AMOUNT).toString());
                object.insert(DapGetTransactionsHistoryCommand::TOKEN,              settingsArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::TOKEN).toString());
                object.insert(DapGetTransactionsHistoryCommand::ADDRESS,            settingsArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::ADDRESS).toString());

                //Adding the transaction time to SettinngArray if it is not specified.
                if(settingsArray.at(i).toVariant().toMap().value(DapGetTransactionsHistoryCommand::TIME).toString().isEmpty())
                {
                    settingsArray.replace(i, object);
                    saveToFile(settingsArray);
                }

                object.insert(DapGetTransactionsHistoryCommand::STATE_TRANSACTION,  DapGetTransactionsHistoryCommand::StateTrasaction::MEMPOOL);
                a_resultArray.append(object);
            }
        }
    }

    for(int settingArrayIndex = 0; settingArrayIndex < settingsArray.count(); settingArrayIndex++)
    {
        bool concide = false;
        for(int fullArrayIndex = 0; fullArrayIndex < a_resultArray.count(); fullArrayIndex++)
        {
            if(settingsArray.at(settingArrayIndex).toVariant().toMap().take(DapGetTransactionsHistoryCommand::HASH).toString() ==
                   a_resultArray.at(fullArrayIndex).toVariant().toMap().take(DapGetTransactionsHistoryCommand::HASH).toString() )
                concide = true;
        }

        if(!concide)
        {
            QJsonObject object;
            object.insert(DapGetTransactionsHistoryCommand::HASH,               settingsArray.at(settingArrayIndex).toVariant().toMap().value(DapGetTransactionsHistoryCommand::HASH).toString());
            object.insert(DapGetTransactionsHistoryCommand::TIME,               settingsArray.at(settingArrayIndex).toVariant().toMap().value(DapGetTransactionsHistoryCommand::TIME).toString());
            object.insert(DapGetTransactionsHistoryCommand::AMOUNT,             settingsArray.at(settingArrayIndex).toVariant().toMap().value(DapGetTransactionsHistoryCommand::AMOUNT).toString());
            object.insert(DapGetTransactionsHistoryCommand::TOKEN,              settingsArray.at(settingArrayIndex).toVariant().toMap().value(DapGetTransactionsHistoryCommand::TOKEN).toString());
            object.insert(DapGetTransactionsHistoryCommand::ADDRESS,            settingsArray.at(settingArrayIndex).toVariant().toMap().value(DapGetTransactionsHistoryCommand::ADDRESS).toString());
            object.insert(DapGetTransactionsHistoryCommand::STATE_TRANSACTION,  DapGetTransactionsHistoryCommand::StateTrasaction::CENCELED);
            a_resultArray.append(object);
        }

    }
}
