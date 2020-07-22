#include "CellframeNodeConfig.h"

CellframeNodeConfig::CellframeNodeConfig(QObject *parent) : QObject(parent)
{

}


CellframeNodeConfig *CellframeNodeConfig::instance(const QString &cfgPath)
{
    static CellframeNodeConfig _instance;
    if (!cfgPath.isEmpty())
        _instance.parseConfig(cfgPath);
    return &_instance;
}


QString CellframeNodeConfig::getDefaultCADir()
{
    //WARNING only Linux default
    return "/opt/cellframe-node/var/lib/ca";
}

QString CellframeNodeConfig::getShareCADir()
{
    //WARNING only Linux default
    return "/opt/cellframe-node/share/ca";
}

bool CellframeNodeConfig::parseConfig(const QString &cfgPath)
{
    Q_UNUSED(cfgPath);
    //dap_config_open
    return true;
}





