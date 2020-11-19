#ifndef DAPNETWORK_H
#define DAPNETWORK_H

#include <QObject>

class DapNetwork: public QObject
{
    Q_OBJECT
public:
    enum State
    {
        ONLINE,
        OFFLINE,
        UNDEFINED
        //...
    };

    Q_INVOKABLE explicit DapNetwork(const QString& a_name, QObject * a_parent = nullptr);

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString state READ stateString NOTIFY stateChanged)
    Q_PROPERTY(QString targetState READ targetStateString NOTIFY targetStateChanged)
    Q_PROPERTY(int activeLinksCount READ activeLinksCount WRITE setActiveLinksCount NOTIFY activeLinksCountChanged)
    Q_PROPERTY(int linksCount READ linksCount WRITE setLinksCount NOTIFY linksCountChanged)
    Q_PROPERTY(QString nodeAddress READ nodeAddress WRITE setNodeAddress NOTIFY nodeAddressChanged)


    int linksCount() const;
    void setLinksCount(int a_linksCount);

    int activeLinksCount() const;
    void setActiveLinksCount(int a_count);

    QString nodeAddress() const;
    void setNodeAddress(const QString &a_nodeAddress);

    QString name() const;
    void setName(const QString &a_name);

    State state() const;
    QString stateString() const;
    void setState(State a_state);
    void setProperties(QVariantMap a_stateMap);

    State targetState() const;
    QString targetStateString() const;
    void setTargetState(State a_targetState);

    static State stringToState(QString a_stateString);

signals:
    void nameChanged(const QString& a_name);

    QString stateChanged(const QString& a_state);

    QString targetStateChanged(const QString& a_targetState);

    void activeLinksCountChanged(int a_count);
    void linksCountChanged(int a_count);
    void nodeAddressChanged(const QString& a_nodeAddress);

private:
    static QString stateToString(State a_state);


    QString m_name;
    State m_state;
    State m_targetState;

    int m_linksCount{};
    int m_activeLinksCount{};
    QString m_nodeAddress;

    static const QMap<State, QString> s_stateStrings;
};

Q_DECLARE_METATYPE(DapNetwork::State)

#endif // DAPNETWORK_H
