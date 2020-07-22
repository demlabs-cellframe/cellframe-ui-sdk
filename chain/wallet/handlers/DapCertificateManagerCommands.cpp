#include "DapCertificateManagerCommands.h"

#include <QJsonDocument>
#include "CertificateManager/DapCertificateOperation.h"



DapCertificateManagerCommands::DapCertificateManagerCommands(const QString &asServicename, QObject *parent
                                                             , const QString &asCliPath, const QString &asToolPath)
    : DapAbstractCommand(asServicename, parent, asCliPath), m_sToolPath(asToolPath)
{

}


//    result = {
//                  command: <enumcommand>
//                  status: "OK" | "FAIL",
//                  errorMessage: "",            //optional when error
//                  data: ...                    //empty or object or array
//             }
//arg1 DapCertificateCommands, arg2...arg10  - аргументы для конкретной команды
QVariant DapCertificateManagerCommands::respondToClient(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, const QVariant &arg10)
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


    qDebug() << "respondToClient, " << DapCertificateCommands::instance()->commandToString(
                    DapCertificateCommands::Commands(arg1.toInt()));

    bool arg1ConvertSuccess = true;
    int command = arg1.toInt(&arg1ConvertSuccess);

    if (!arg1ConvertSuccess) {
        qCritical() << "command not responsed";
        return QJsonObject({
                               { "command", DapCertificateCommands::UnknownCommand }
                             , { "status", "FAIL" }
                             , { "errorMessage", "command not responsed" }
                           });
    }


    QString status = DapCertificateCommands::statusOK();
    QString errorMessage;
    QVariant result;


    switch (command) {
        case DapCertificateCommands::GetSertificateList:
            result = DapCertificateOperation::getCertificateList(status, errorMessage);
            break;
        case DapCertificateCommands::CreateCertificate: {
                QVariantMap metaData = QJsonDocument::fromJson(arg4.toString().toUtf8()).toVariant().value<QVariantMap>();
                result = DapCertificateOperation::createCertificate(arg2.toString(), arg3.toString(), metaData
                                                                    , status, errorMessage, m_sToolPath);
            }
            break;
        case DapCertificateCommands::DumpCertifiacate:
            result = DapCertificateOperation::dumpCertificateFile(arg2.toString(), arg3.toString(), status, errorMessage);   //this cliPath to tools_path
            break;
        case DapCertificateCommands::ImportCertificate:
            //TODO
            break;
        case DapCertificateCommands::ExportPublicCertificateToFile:
            result = DapCertificateOperation::exportPublicCertificateToFile(arg2.toString(), arg3.toString(), status, errorMessage, m_sToolPath);
            break;
        case DapCertificateCommands::ExportPublicCertificateToMempool:
            result = DapCertificateOperation::exportPublicCertificateToMempool(arg2.toString(), arg3.toString(), status, errorMessage, m_sCliPath);
            break;
        case DapCertificateCommands::AddSignatureToCertificate:
            //TODO
            break;
        case DapCertificateCommands::DeleteCertificate:
            result = DapCertificateOperation::deleteCertificate(arg2.toString(), status, errorMessage);
            break;
        case DapCertificateCommands::UpdateCertificateList:
            //вообще команда только для клиента, если произошел запрос к сервисы то выполняем тоже что и при получении списка
            result = DapCertificateOperation::getCertificateList(status, errorMessage);
            break;

        default:
            command = command < DapCertificateCommands::UnknownCommand && command > DapCertificateCommands::UpdateCertificateList
                      ? DapCertificateCommands::UnknownCommand : command;
            break;
    }


//    QJsonValue value;

//   QJsonArray response;
//   response.append(QJsonValue(arg1.toString()));
//   response.append(QJsonValue("resultDataCert"));
//    QJsonDocument doc;
//    doc[]
//     doc.toBinaryData()


    return QJsonObject({
                           { "command", command }
                         , { "status", status }
                         , { "errorMessage", errorMessage }
                         , { "data", QJsonValue::fromVariant(result) }
                       });

}  //respondToClient



void DapCertificateManagerCommands::notifedFromService(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4
                                                       , const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8
                                                       , const QVariant &arg9, const QVariant &arg10)
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

    qInfo() << "DapCertificateManagerCommands::notifedFromService" << arg1 << arg2 << arg3 << arg4;


    bool arg1ConvertSuccess = true;
    int command = arg1.toInt(&arg1ConvertSuccess);

    if (!arg1ConvertSuccess) {
        qCritical() << "command not responsed";
        return ;
    }


    QString status = arg2.toString();
    if (!(status == DapCertificateCommands::statusOK()
          || status == DapCertificateCommands::statusFAIL()))  //правильней будет валидировать статус
    {
        status = DapCertificateCommands::statusFAIL();
    }

    QString errorMessage = arg3.toString();
    const QVariant& response = arg4;
    QVariant result;

    switch (command) {
        case DapCertificateCommands::UpdateCertificateList:
            result = response;
            break;
    }


    emit clientNotifed(QVariant(QJsonObject({
                                                { "command", command }
                                              , { "status", status }
                                              , { "errorMessage", errorMessage }
                                              , { "data", QJsonValue::fromVariant(result) }
                                            })
                                ));
}    //notifedFromService

















