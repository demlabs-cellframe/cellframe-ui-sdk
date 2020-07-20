#ifndef DAPCERTIFICATEOPERATION_H
#define DAPCERTIFICATEOPERATION_H


#include <QObject>
#include <QJsonDocument>
#include <QFileInfo>
#include "DapCertificateType.h"
#include "dap_cert.h"


class DapCertificateOperation : public QObject
{
    Q_OBJECT
public:



    static bool addMetaDataToCert(const QString& certName, const QVariantMap& metaData, const QString& s_toolPath);


//    static bool addMetaDataToCert(dap_cert_t* certFile, const QVariantMap& metaData);

    //создание сертификата
    static QJsonObject createCertificate(const QString& certName, const QString& signatureType, const QVariantMap &metaData
                                         , QString& status, QString& errorMessage, const QString& s_toolPath);


    static QJsonObject deleteCertificate(const QString& fileName, QString& status, QString& errorMessage);

//    //получение информации о сертификате через -tool, не работает для папки публичных сертификатов
//    static QJsonObject dumpCertificate(const QString& certName, QString& status, QString& errorMessage, const QString& s_toolPath);

    //получение информации о сертификате через файл
    static QJsonObject dumpCertificateFile(const QString& certName, const QString& filePath
                                       , QString& status, QString& errorMessage);

    //проверка того что сертификат создан, не работает для папки публичных сертификатов
    static bool existsCertificate(const QString& certName, const QString& s_toolPath);


    static QJsonObject exportPublicCertificateToFile(const QString& certName, const QString& newCertName
                                       , QString& status, QString& errorMessage, const QString& s_toolPath);

    static QJsonObject exportPublicCertificateToMempool(const QString& network, const QString& certName
                                       , QString& status, QString& errorMessage, const QString &s_cliPath);



    //возвращает тип доступа ключа из файла сертификата
    static DapCertificateType::AccessKeyType getAccessKeyType(const QString& certFilePath);

    //возвращает тип доступа ключа из объекта файла сертификата
    static DapCertificateType::AccessKeyType getAccessKeyType(dap_cert_t* certFile);


    static QJsonArray getCertificateList(QString& status, QString& errorMessage);

    static QJsonObject getSimpleCertificateInfo(const QFileInfo &info, const DapCertificateType::DirType& dirType);


};




#endif // DAPCERTIFICATEOPERATION_H
