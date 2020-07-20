#ifndef DAPCERTIFICATEMANAGERCOMMNADS_H
#define DAPCERTIFICATEMANAGERCOMMNADS_H


#include <QObject>
#include <QString>
#include "DapAbstractCommand.h"
#include "CertificateManager/DapCertificateCommands.h"
#include "CertificateManager/DapCertificateType.h"
#include "CellframeNodeConfig.h"


/*
    как видно из названия выполняет команды для модуля сертификатов,
    но выполняет несколько команд, тип команды передается первым параметром, все допустимые команды прописаны в перечислении

    cliPath должен содержать путь до cellframe-node-tool
*/





class DapCertificateManagerCommands : public DapAbstractCommand
{
    Q_OBJECT          //need
public:
    /// Overloaded constructor.
    /// @param asServiceName Service name.
    /// @param parent Parent.
    /// @details The parent must be either DapRPCSocket or DapRPCLocalServer.
    /// @param asCliPath The path to cli nodes.
    DapCertificateManagerCommands(const QString &asServicename, QObject *parent = nullptr
                                  , const QString &asCliPath = QString(), const QString &asToolPat = QString());


public slots:
    /// Send a response to the client.
    /// @details Performed on the service side.
    /// @param arg1...arg10 Parameters. arg1 must be command from DapCertificateCommands
    /// @return Reply to client.
    QVariant respondToClient(const QVariant &arg1 = QVariant(), const QVariant &arg2 = QVariant(),
                             const QVariant &arg3 = QVariant(), const QVariant &arg4 = QVariant(),
                             const QVariant &arg5 = QVariant(), const QVariant &arg6 = QVariant(),
                             const QVariant &arg7 = QVariant(), const QVariant &arg8 = QVariant(),
                             const QVariant &arg9 = QVariant(), const QVariant &arg10 = QVariant()) override;


    //перехватываем нотификации от сервиса, может быть избыточно
    //неочевидно что испускаемые сигналы этого класса будут подключены к одному связаному с этой командой сигналу в DapServiceController
    void notifedFromService(const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4
                            , const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8
                            , const QVariant &arg9, const QVariant &arg10) override;




private:
    QString m_sToolPath;


};




#endif // DapCertificateManagerCommands_H
