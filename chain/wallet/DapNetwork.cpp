#include "DapNetwork.h"
#include <QMap>
#include <QJsonObject>
#include <QDebug>

const QString DapNetwork::NAME {"name"};
const QString DapNetwork::STATE {"state"};
const QString DapNetwork::TARGET_STATE {"targetState"};
const QString DapNetwork::NODE_ADDRESS {"nodeAddress"};

const QMap<DapNetwork::State, QString> DapNetwork::s_stateStrings = {
    { DapNetwork::State::OFFLINE, "NET_STATE_OFFLINE"},
    { DapNetwork::State::OFFLINE, "NET_STATE_ONLINE"}
};


DapNetwork::DapNetwork(const QString& a_name, QObject * a_parent /*= nullptr*/)
    : QObject(a_parent)
    , m_name(a_name)
{
}

int DapNetwork::linksCount() const
{
    return m_linksCount;
}

void DapNetwork::setLinksCount(int a_linksCount)
{
    m_linksCount = a_linksCount;
}

int DapNetwork::activeLinksCount() const
{
    return m_activeLinksCount;
}

void DapNetwork::setActiveLinksCount(int a_count)
{
    if (m_activeLinksCount == a_count)
        return;

    m_activeLinksCount = a_count;
    emit this->activeLinksCountChanged(a_count);
}

QString DapNetwork::nodeAddress() const
{
    return m_nodeAddress;
}

void DapNetwork::setNodeAddress(const QString &a_nodeAddress)
{
    if (m_nodeAddress == a_nodeAddress)
        return;

    m_nodeAddress = a_nodeAddress;
    emit this->nodeAddressChanged(a_nodeAddress);
}

QString DapNetwork::name() const
{
    return m_name;
}

DapNetwork::State DapNetwork::state() const
{
    return m_state;
}

QString DapNetwork::stateString() const
{
    return DapNetwork::stateToString(m_state);
}

void DapNetwork::setName(const QString &a_name)
{
    if (m_name == a_name)
        return;

    m_name = a_name;
    emit this->nameChanged(a_name);
}

void DapNetwork::setState(DapNetwork::State a_state)
{
    if (m_state == a_state)
        return;
    m_state = a_state;

    emit this->stateChanged(DapNetwork::stateToString(a_state));
}

void DapNetwork::setProperties(QVariantMap a_stateMap)
{
    QJsonValue jsonValue;

    if (a_stateMap.contains(STATE))
        this->setTargetState(DapNetwork::stringToState(a_stateMap[STATE].toString()));

    if (a_stateMap.contains(TARGET_STATE))
        this->setTargetState(DapNetwork::stringToState(a_stateMap[TARGET_STATE].toString()));

    if (this->nodeAddress().isEmpty()) //Is not necrssary to set node address if already set
    {
        if (a_stateMap.contains(NODE_ADDRESS))
            this->setNodeAddress(a_stateMap[NODE_ADDRESS].toString());
    }
}

DapNetwork::State DapNetwork::targetState() const
{
    return m_targetState;
}

QString DapNetwork::targetStateString() const
{
    return DapNetwork::stateToString(m_targetState);
}

void DapNetwork::setTargetState(DapNetwork::State a_targetState)
{
    if (m_targetState == a_targetState)
        return;
    m_targetState = a_targetState;

    emit this->targetStateChanged(DapNetwork::stateToString(a_targetState));
    //    emit this->targetStateChanged(a_targetState);
}

DapNetwork::State DapNetwork::stringToState(QString a_stateString)
{
    return s_stateStrings.key(a_stateString);
}

QString DapNetwork::stateToString(DapNetwork::State a_state)
{
    return s_stateStrings.value(a_state);
}

