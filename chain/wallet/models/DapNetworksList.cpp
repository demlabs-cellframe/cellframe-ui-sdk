#include "DapNetworksList.h"
#include <QDebug>
#include <QJsonObject>

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

DapNetwork *DapNetworksList::addIfNotExist(const QString &a_name)
{
    DapNetwork* network = this->findNetwork(a_name);

    if (!network)
    {
        network = this->add(a_name);
        emit this->modelChanged();
    }
    return  network;
}

QList<DapNetwork*> DapNetworksList::fill(QStringList a_NetworksNames)
{
    QList<DapNetwork*> newNetworks;
    for (QString curNetworkName: a_NetworksNames)
    {
        DapNetwork* network = this->findNetwork(curNetworkName);
        if (!network)
            newNetworks.append(this->add(curNetworkName));
    }

    if (!newNetworks.isEmpty())
        emit this->modelChanged();

    return newNetworks;
}

DapNetwork* DapNetworksList::add(const QString &a_networkName)
{
    DapNetwork* newNetwork = new DapNetwork(a_networkName, this);
    m_networks.append(newNetwork);
    emit this->networkAdded(newNetwork);

    return  newNetwork;
}

const QList<DapNetwork *> &DapNetworksList::all()
{
    return m_networks;
}

bool DapNetworksList::isEmpty() const
{
    return m_networks.isEmpty();
}
