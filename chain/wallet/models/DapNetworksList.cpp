#include "DapNetworksList.h"

DapNetworksList::DapNetworksList(QObject *a_parrent /*= nullptr*/)
    :QObject(a_parrent)
{

}

QList<QObject *> DapNetworksList::model()
{
    QList<QObject*> listModel;
    for (DapNetwork* curNetwork: m_networks)
    {
        listModel.append(curNetwork);
    }
    return listModel;
}
