#pragma once

#include <QSettings>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include "handlers/DapGetTransactionsHistoryCommand.h"

class DapSaveTransaction
{
public:
    static const QString TRANSACRIONS_COUNT;

    DapSaveTransaction();

    static void saveTransactionBySpecifyingTime(const QString a_hash, const QString &a_time, const QString &a_amount, const QString &a_token, const QString &a_address);
    static void creatLocalHistory(QJsonArray& a_resultArray, QJsonArray& a_mempoolArray);
    static QJsonArray readFomFile();
    static void saveToFile(QJsonArray &a_array);
    static void saveToFileFromCreat(QJsonArray &a_array);


};

