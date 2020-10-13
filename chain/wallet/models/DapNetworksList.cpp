#include "DapNetworksList.h"
#include <QDebug>

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

DapNetwork *DapNetworksList::findNetwork(const QString &a_name)
{

    auto it = std::find_if(m_networks.begin(), m_networks.end(), [a_name](DapNetwork* a_network){
        return a_network->name() == a_name;
    });
    if (it == m_networks.end())
        return nullptr;
    return *it;
}

void DapNetworksList::fill(QVariant a_stringList)
{
    if (!a_stringList.isValid() || !a_stringList.canConvert<QStringList>())
    {
        qWarning() << "wrong parametr in DapNetworksList::fill";
        return;
    }

    for (QString curNetworkName: a_stringList.toStringList())
    {
        DapNetwork* network = this->findNetwork(curNetworkName);
        if (!network)
        {
            network = new DapNetwork(curNetworkName, this);
            m_networks.append(network);
            //TODO: get state
        }
    }
}
