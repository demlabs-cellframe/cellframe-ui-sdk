#ifndef CELLFRAMENODECONFIG_H
#define CELLFRAMENODECONFIG_H


#include <QObject>
#include <QString>


/*
    part common module

    нужно вручную получать путь к файлу конфигураций на разных платформах и парсить его

    сейчас только заглушки для линукса
    //TODO
*/



class CellframeNodeConfig : public QObject
{
    Q_OBJECT
public:
    static CellframeNodeConfig* instance(const QString& cfgPath = "");

    Q_INVOKABLE QString getDefaultCADir();
    Q_INVOKABLE QString getShareCADir();

    Q_INVOKABLE bool parseConfig(const QString& cfgPath);

signals:


private:
     explicit CellframeNodeConfig(QObject *parent = nullptr);

};




#endif // CellframeNodeConfig_H
