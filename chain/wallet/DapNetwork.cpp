#include "DapNetwork.h"
#include <QMap>
#include <QJsonObject>
#include <QDebug>

const QMap<QString, DapNetwork::State> DapNetwork::s_stateStrings = {
    { "NET_STATE_OFFLINE", DapNetwork::State::OFFLINE},
    { "NET_STATE_ONLINE", DapNetwork::State::ONLINE},
    { "NET_STATE_LINKS_PREPARE", DapNetwork::State::INKS_PREPARE},
    { "NET_STATE_LINKS_CONNECTING", DapNetwork::State::LINKS_CONNECTING},
    { "NET_STATE_SYNC_CHAINS", DapNetwork::State::SYNC_CHAINS},
    { "NET_STATE_SYNC_GDB", DapNetwork::State::SYNC_GDB},
    { "UNDEFINED", DapNetwork::State::UNDEFINED}
};

const QMap<DapNetwork::State, QString> DapNetwork::s_stateRepresentations = {
    { DapNetwork::State::OFFLINE         , "OFFLINE"},
    { DapNetwork::State::ONLINE          , "ONLINE"},
    { DapNetwork::State::INKS_PREPARE    , "LINKS PREPARE"},
    { DapNetwork::State::LINKS_CONNECTING, "LINKS CONNECTING"},
    { DapNetwork::State::SYNC_CHAINS     , "SYNC CHAINS"},
    { DapNetwork::State::SYNC_GDB        , "SYNC GDB"},
    { DapNetwork::State::UNDEFINED       , "UNDEFINED"}
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
    if (m_linksCount == a_linksCount)
        return;
    m_linksCount = a_linksCount;

    emit this->linksCountChanged(a_linksCount);
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

QString DapNetwork::stateRepresentation() const
{
    return DapNetwork::toRepresentation(m_state);
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

    emit this->stateChanged(a_state);
    emit this->stateRepresentationChanged(DapNetwork::toRepresentation(a_state));
}

DapNetwork::State DapNetwork::targetState() const
{
    return m_targetState;
}

QString DapNetwork::targetStateRepresentation() const
{
    return DapNetwork::toRepresentation(m_targetState);
}

void DapNetwork::setTargetState(DapNetwork::State a_targetState)
{
    if (m_targetState == a_targetState)
        return;
    m_targetState = a_targetState;

    emit this->targetStateChanged(a_targetState);
    emit this->targetStateRepresentationChanged(DapNetwork::toRepresentation(a_targetState));
}

DapNetwork::State DapNetwork::toState(QString a_stateString)
{
    return s_stateStrings.value(a_stateString, State::UNDEFINED);
}

QString DapNetwork::toRepresentation(DapNetwork::State a_state)
{
    return s_stateRepresentations.value(a_state);
}

