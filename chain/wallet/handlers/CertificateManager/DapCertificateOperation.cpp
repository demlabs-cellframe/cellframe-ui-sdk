#include "DapCertificateOperation.h"
#include <QString>

#include "DapCertificateType.h"
#include "DapCertificateCommands.h"
#include "CellframeNodeConfig.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>


#include "dap_cert_file.h"
#include "dap_binary_tree.h"
#include "dap_common.h"
#include "dap_config.h"
#include "dap_string.h"
#include "dap_strfuncs.h"



bool DapCertificateOperation::addMetaDataToCert(const QString &certName, const QVariantMap& metaData, const QString &s_toolPath)
{
    Q_UNUSED(certName)
    Q_UNUSED(s_toolPath)

    auto iterator = metaData.constBegin();
    while (iterator != metaData.constEnd()) {
        QString value = iterator.value().toString();
        QProcess process;

        QString args;
//        if (iterator.key() == "creation_date" || iterator.key() == "expiration_date") {      //TODO add date custom
//            args = QString("%1 cert add_metadata %2 %3")
//                                   .arg(s_toolPath).arg(certName).arg(QString("%1:%2:%3:%4")    //  :%3:%4"  key:type:length:value
//                                                                          .arg(iterator.key())
//                                                                          .arg(dap_cert_metadata_type::DAP_CERT_META_DATETIME)
//                                                                          .arg(value.size())
//                                                                          .arg(value)
//                                                                       );
//        } else {
            args = QString("%1 cert add_metadata %2 %3")
                                   .arg(s_toolPath).arg(certName).arg(QString("%1:%2:%3:%4")    //  key:type:length:value
                                                                          .arg(iterator.key())
                                                                          .arg(dap_cert_metadata_type::DAP_CERT_META_STRING)
                                                                          .arg(value.size())
                                                                          .arg(value)
                                                                       );
//        }

        args = args.toLatin1();

        process.start(args);
        process.waitForFinished(-1);
        qDebug() << args << "\naddMetaDataToCert result:" << process.readAll();

        ++iterator;
    }   //


    return true;
}


//bool DapCertificateOperation::addMetaDataToCert(dap_cert_t *certFile, const QVariantMap &metaData)
//{
//    auto iterator = metaData.constBegin();
//    while (iterator != metaData.constEnd()) {
////        QString value = iterator.value().toString();

////        QString(":%1:%2:%3")    //  :%3:%4"  key:type:length:value
////                .arg(dap_cert_metadata_type::DAP_CERT_META_STRING)
////                .arg(value.size())
////                .arg(value)
////                ;

//        ++iterator;
//    }   //

//    return true;
//}


QJsonObject DapCertificateOperation::createCertificate(const QString &certName, const QString &signatureType, const QVariantMap &metaData
                                                       , QString &status, QString &errorMessage, const QString& s_toolPath)
{
    QFileInfo info(CellframeNodeConfig::instance()->getDefaultCADir() + QString("/%1.dcert").arg(certName) );


    if (info.exists()){
        status = DapCertificateCommands::statusFAIL();
        errorMessage = tr("Certificate is exists");

        return QJsonObject({
                               { "fileName", certName }
                          });
    }


    static const QMap<QString, dap_enc_key_type_t> convertSignatureType = QMap<QString, dap_enc_key_type_t>({
                                                                          { "dilithium", DAP_ENC_KEY_TYPE_SIG_DILITHIUM }
                                                                        , { "picnic", DAP_ENC_KEY_TYPE_SIG_PICNIC }
                                                                        , { "bliss", DAP_ENC_KEY_TYPE_SIG_BLISS }
                                                                        , { "tesla", DAP_ENC_KEY_TYPE_SIG_TESLA }
                                                                    });

    QProcess process;
    auto args = QString("%1 cert create %2 %3").arg(s_toolPath).arg(certName).arg(signatureType);
    process.start(args);
    process.waitForFinished(-1);
    process.close();
    //QString processResult = QString::fromLatin1(process.readAll());

    info.refresh();

    if (info.exists()) {       //existsCertificate(certName, s_toolPath)
        qDebug() << "add cert metaData" << metaData.size();
        addMetaDataToCert(certName, metaData, s_toolPath);

        //TODO check error add metadata

        return QJsonObject({
                               { "fileName", info.fileName() }
                             , { "completeBaseName", info.completeBaseName() }
                             , { "filePath", info.filePath() }
                             , { "dirType", DapCertificateType::DefaultDir }
                             , { "accessKeyType", DapCertificateType::Both  }     //getAccessKeyType(newCert)
                         });
    } else {
        status = DapCertificateCommands::statusFAIL();
        errorMessage = tr("Certificate not created");

        return QJsonObject({
                               { "fileName", certName }
                          });
    }

}   //createCertificate


QJsonObject DapCertificateOperation::deleteCertificate(const QString& filePath, QString& status, QString& errorMessage)
{
    Q_UNUSED(status)
    Q_UNUSED(errorMessage)

    if (!QFile::remove(filePath)) {
        status = DapCertificateCommands::statusFAIL();
        errorMessage = tr("File not deleted.");
    }

    return QJsonObject({
                          { "deletedFilePath", filePath }
                      });
}


//QJsonObject DapCertificateOperation::dumpCertificate(const QString &certName, QString &status, QString &errorMessage
//                                                     , const QString &s_toolPath)
//{
//    QProcess process;
//    auto args = QString("%1 cert dump %2 %3").arg(s_toolPath).arg(certName);
//    process.start(args);
//    process.waitForFinished(-1);
//    QString processResult = QString::fromLatin1(process.readAll());

//    //считаем что если ответ пустой то сертификата нет, но это актуально только для дефолтной папки сертификатов
//    if (processResult.isEmpty()) {
//        status = DapCertificateCommands::statusFAIL();
//        errorMessage = tr("Certificate not find");
//    }

//    return QJsonObject({
//                            { "certName", certName }
//                       });
//}


QJsonObject DapCertificateOperation::dumpCertificateFile(const QString &certName, const QString &filePath, QString &status
                                                         , QString &errorMessage)
{
    Q_UNUSED(certName)
    Q_UNUSED(filePath)
    Q_UNUSED(status)
    Q_UNUSED(errorMessage)


    QJsonObject result;
    result.insert("filePath", filePath);

    dap_cert_t* certFile = dap_cert_file_load(qPrintable(filePath));

    if (certFile == nullptr) {
        status = DapCertificateCommands::statusFAIL();
        errorMessage = tr("Certificate does not exist");
        result.insert("name", certName);

        return result;
    }


    auto parseCertFile{
        [&result](dap_cert_t * a_cert) {    // -> bool
            result.insert("name", QJsonValue::fromVariant(QString(a_cert->name)));
            result.insert("signature", QJsonValue::fromVariant(QString(dap_sign_type_to_str( dap_sign_type_from_key_type(a_cert->enc_key->type) ))));
            result.insert("privateKeySize", QJsonValue::fromVariant(QVariant::fromValue(a_cert->enc_key->priv_key_data_size)));
            result.insert("publicKeySize", QJsonValue::fromVariant(QVariant::fromValue(a_cert->enc_key->pub_key_data_size)));
            size_t l_meta_items_cnt = dap_binary_tree_count(a_cert->metadata);
            result.insert("metaSectionCount", QJsonValue::fromVariant(QVariant::fromValue(l_meta_items_cnt)));
            result.insert("signatureChainSize", QJsonValue::fromVariant(QVariant::fromValue(dap_cert_count_cert_sign (a_cert))));

            QJsonArray metadata;

            if (l_meta_items_cnt) {
                printf ("Metadata sections\n");
                dap_list_t *l_meta_list = dap_binary_tree_inorder_list(a_cert->metadata);
                dap_list_t *l_meta_list_item = dap_list_first(l_meta_list);
                while (l_meta_list_item) {
                    dap_cert_metadata_t *l_meta_item = (dap_cert_metadata_t *)l_meta_list_item->data;
                    char *l_str;
                    QString key, value;
                    int type = l_meta_item->type;
                    int length = 0;

                    switch (l_meta_item->type) {
                        case DAP_CERT_META_STRING:
                            l_str = strndup((char *)l_meta_item->value, l_meta_item->length);

                            key = l_meta_item->key;
                            length = l_meta_item->length;
                            value = l_str;

                            free(l_str);
                            break;
                        case DAP_CERT_META_INT:
                        case DAP_CERT_META_BOOL:
                            key = l_meta_item->key;
                            length = l_meta_item->length;
                            value = l_str;
                            break;
                        default:
                            l_str = l_meta_item->length ? DAP_NEW_Z_SIZE(char, l_meta_item->length * 2 + 1) : NULL;
                            dap_bin2hex(l_str, l_meta_item->value, l_meta_item->length);
                            key = l_meta_item->key;
                            length = l_meta_item->length;
                            value = l_str;
//                            printf("%s\t%u\t%u\t%s\n", l_meta_item->key, l_meta_item->type, l_meta_item->length, l_str);
                            DAP_DELETE(l_str);
                            break;
                    }  //switch

                    metadata.append(QJsonObject({
                                                    { "key", key }
                                                  , { "type", type }
                                                  , { "length", length }
                                                  , { "value", value }
                                                }));

                    l_meta_list_item = l_meta_list_item->next;
                }
                dap_list_free(l_meta_list);
            }  //if meta_item_cnt

            result.insert("metadata", metadata);
        }
    };


    parseCertFile(certFile);

    dap_cert_delete(certFile);

    return result;
}


bool DapCertificateOperation::existsCertificate(const QString &certName, const QString &s_toolPath)
{
    QProcess process;
    process.start(QString("%1 cert dump %2").arg(s_toolPath).arg(certName));
    process.waitForFinished(-1);
    QString result(QString::fromLatin1(process.readAll()));
    //qDebug() << "DapCertificateOperation::existsCertificate" << certName << s_toolPath << result;
    return !result.isEmpty();
}


QJsonObject DapCertificateOperation::exportPublicCertificateToFile(const QString &certName, const QString &newCertName, QString &status
                                                                   , QString &errorMessage, const QString& s_toolPath)
{
    //WARNING сертификат с публичным ключом создается в папке обычных сертификатов
    QString filePath = QString("%1/%2.dcert").arg(CellframeNodeConfig::instance()->getDefaultCADir()).arg(newCertName);
    QFileInfo info(filePath);

    if (info.exists()) {
        status = DapCertificateCommands::statusFAIL();
        errorMessage = tr("Certificate is exists");
        return QJsonObject({
                        { "fileName", newCertName + ".dcert" }
                      , { "completeBaseName", newCertName }
                      , { "filePath", filePath }
                      , { "dirType", DapCertificateType::DefaultDir }
                      , { "accessKeyType", DapCertificateType::Public }     //getAccessKeyType(newCert)
                  });
    }

    QProcess process;
    QString args(QString("%1 cert create_cert_pkey %2 %3").arg(s_toolPath).arg(certName).arg(newCertName));
    process.start(args);
    process.waitForFinished(-1);

    QString result(process.readAll());
    //WARNING в результате всегда пусто!
    if (!result.isEmpty()) {
        //TODO check process result
    }

    //qDebug() << args << "\nexportPublicCertificateToFile" << filePath << ", result:" << result;
    info.refresh();
    return getSimpleCertificateInfo(info, DapCertificateType::DefaultDir);
}


QJsonObject DapCertificateOperation::exportPublicCertificateToMempool(const QString &network, const QString &certName, QString &status
                                                                      , QString &errorMessage, const QString& s_cliPath)
{
    QProcess process;
    QString args(QString("%1 mempool_add_ca -net %2 -ca_name %3").arg(s_cliPath).arg(network).arg(certName));   // newCertName
    process.start(args);
    process.waitForFinished(-1);

    QString result(process.readAll());     //WARNING тут тоже ответ пустой
    if (result.isEmpty()) {

    } else {

    }

    //qDebug() << args << "\nexportPublicCertificateToMempool" << certName << network << ", result:" << result;

    return QJsonObject({
                    { "certName", certName }
                  , { "network", network }
              });
}


DapCertificateType::AccessKeyType DapCertificateOperation::getAccessKeyType(const QString &certFilePath)
{
    dap_cert_t* certFile = dap_cert_file_load(qPrintable(certFilePath));
    if (certFile == nullptr){
        qCritical() << "file not open" << certFilePath;
        return DapCertificateType::Public;
        //WARNING нужна более продвинутая обработка ошибок, но по умолчанию вызов этой функции проиходит сразу после получение списка файлов
    }

    auto result = getAccessKeyType(certFile);
    dap_cert_delete(certFile);
    return result;
}


DapCertificateType::AccessKeyType DapCertificateOperation::getAccessKeyType(dap_cert_t *certFile)
{
    int privateKeySize = certFile->enc_key->priv_key_data_size;
    int publicKeySize = certFile->enc_key->pub_key_data_size;

    if (privateKeySize > 0 && publicKeySize > 0) {
        return DapCertificateType::Both;
    } else if (publicKeySize > 0){
        return DapCertificateType::Public;
    }

    return DapCertificateType::Private;
}


QJsonArray DapCertificateOperation::getCertificateList(QString& status, QString& errorMessage)
{
    Q_UNUSED(status)
    Q_UNUSED(errorMessage)

    QJsonArray result;

    auto parseDir =
        [&result](const QString& dirPath, const DapCertificateType::DirType& dirType) -> bool
        {
            QDir dir(dirPath);

            if (!dir.exists()) {
                qWarning() << "The directory does not exist:" << dirPath;
                return false;
            }

            dir.setFilter(QDir::Files);      //only files in derictory
            dir.setSorting(QDir::Name);      //set sort by name

            QFileInfoList list = dir.entryInfoList();   // get all QFileInfo for files in dir

            foreach (const QFileInfo& info, list) {
                if (info.suffix() == "dcert") {       //выбираем только файлы сертификатов с расширением dcert
                    result.append(getSimpleCertificateInfo(info, dirType));
                }

            }

            return true;
        };


    //предполагаем что в разных папках лежат, разные ключи.
    parseDir(CellframeNodeConfig::instance()->getDefaultCADir(), DapCertificateType::DefaultDir );
    parseDir(CellframeNodeConfig::instance()->getShareCADir(), DapCertificateType::ShareDir );


    return result;
}


QJsonObject DapCertificateOperation::getSimpleCertificateInfo(const QFileInfo &info, const DapCertificateType::DirType& dirType)
{
    return QJsonObject({
                            { "fileName", info.fileName() }
                          , { "completeBaseName", info.completeBaseName() }
                          , { "filePath", info.filePath() }
                          , { "dirType", dirType }
                          , { "accessKeyType", getAccessKeyType(info.filePath()) }
                      });
}








