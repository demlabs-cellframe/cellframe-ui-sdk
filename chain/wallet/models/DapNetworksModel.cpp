#include "DapNetworksModel.h"

#include <QVariant>

#include "DapNetwork.h"

DapNetworksModel::DapNetworksModel()
{

}

DapNetwork *DapNetworksModel::find(const QString &a_name)
{
    auto it = std::find_if(m_networks.begin(), m_networks.end(), [a_name](DapNetwork* a_network){
        return a_network->name() == a_name;
    });

    if (it == m_networks.end())
        return nullptr;

    return *it;
}

DapNetwork *DapNetworksModel::addIfNotExist(const QString &a_name, bool* a_wasCreated /*= nullptr*/)
{
    DapNetwork* network = this->find(a_name);

    if (!network)
    {
        network = new DapNetwork(a_name, this);
        this->append(network);

        if (a_wasCreated)
            *a_wasCreated = true;
    }
    else if (a_wasCreated)
        *a_wasCreated = false;

    return network;
}

QStringList DapNetworksModel::names()
{
    QStringList namesList;
    for (auto curNetwork: this->all()) {
        namesList.append(curNetwork->name());
    }
    return namesList;
}

const QList<DapNetwork *> &DapNetworksModel::all() const
{
    return m_networks;
}

bool DapNetworksModel::isEmpty() const
{
    return m_networks.isEmpty();
}

int DapNetworksModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_networks.count();
}

QVariant DapNetworksModel::data(const QModelIndex &index, int role) const
{
    auto networkAtIndex = m_networks.value(index.row());

    if (!index.isValid()) return QVariant();
    switch (role)
    {
        case Qt::DisplayRole:
    case Roles::NETWORK: return QVariant::fromValue<QObject*>(networkAtIndex);
    }
    return QVariant();
}

void DapNetworksModel::append(DapNetwork *a_network)
{
    if (!a_network)
        return;

    int lastIndex = m_networks.count() ;


    beginInsertRows(QModelIndex(), lastIndex, lastIndex);

    m_networks.append(a_network);

    endInsertRows();
}


QHash<int, QByteArray> DapNetworksModel::roleNames() const
{
    return {
        {NETWORK, "network"},
    };
}
