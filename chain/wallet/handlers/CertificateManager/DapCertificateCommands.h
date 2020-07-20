#ifndef DAPCERTIFICATECOMMANDS_H
#define DAPCERTIFICATECOMMANDS_H

#include <QObject>


//one instance class in qml
//with enum commands and service name


class DapCertificateCommands : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serviceName READ getServiceName CONSTANT)
    Q_PROPERTY(QString statusOK READ getStatusOK CONSTANT)
    Q_PROPERTY(QString statusFAIL READ getStatusFAIL CONSTANT)

public:
    static DapCertificateCommands* instance();

    enum Commands{                         //maybe need class
        UnknownCommand = 0,                //return by default and in error case
        GetSertificateList,
        CreateCertificate,
        DumpCertifiacate,                  //получение информации о сертификате
        ImportCertificate,
        ExportPublicCertificateToFile,
        ExportPublicCertificateToMempool,
        AddSignatureToCertificate,      //WARNING нереализовано
        DeleteCertificate,
        UpdateCertificateList           //уведомление только если изменяется папка сертификатов вручную
    };
    Q_ENUM(Commands);

    //возвращает строковоe представление перечисления
    Q_INVOKABLE QString commandToString(Commands command);

    //for access serviceName in qml
    QString getServiceName() const { return serviceName(); };
    static QString serviceName() { return QString("DapCertificateManagerCommands"); };

    //for access enum status result
    QString getStatusOK() const { return statusOK(); };
    QString getStatusFAIL() const { return statusFAIL(); };

    static QString statusOK() { return QString("OK"); };
    static QString statusFAIL() { return QString("FAIL"); };



protected:
    explicit DapCertificateCommands() {  }

};




#endif // DAPCERTIFICATECOMMANDS_H
