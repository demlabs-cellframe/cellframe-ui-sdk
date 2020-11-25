#ifndef DAPNETWORK_H
#define DAPNETWORK_H

#include <QObject>

class DapNetwork: public QObject
{
    Q_OBJECT
public:
    Q_ENUMS(State)
    enum State
    {
        ONLINE,
        OFFLINE,
        INKS_PREPARE,
        LINKS_CONNECTING,
        SYNC_CHAINS,
        UNDEFINED
        //...
    };

    Q_INVOKABLE explicit DapNetwork(const QString& a_name, QObject * a_parent = nullptr);
    explicit DapNetwork(QObject * a_parent = nullptr) : QObject(a_parent){}

    Q_PROPERTY(QString  name                        READ name                       WRITE setName NOTIFY nameChanged)

    Q_PROPERTY(State    state                       READ state                      NOTIFY stateChanged)
    Q_PROPERTY(QString  stateRepresentation         READ stateRepresentation        NOTIFY stateRepresentationChanged)

    Q_PROPERTY(State    targetState                 READ targetState                NOTIFY targetStateChanged)
    Q_PROPERTY(QString  targetStateRepresentation   READ targetStateRepresentation  NOTIFY targetStateRepresentationChanged)

    Q_PROPERTY(int      activeLinksCount            READ activeLinksCount           WRITE setActiveLinksCount NOTIFY activeLinksCountChanged)
    Q_PROPERTY(int      linksCount                  READ linksCount                 WRITE setLinksCount NOTIFY linksCountChanged)

    Q_PROPERTY(QString  nodeAddress                 READ nodeAddress                WRITE setNodeAddress NOTIFY nodeAddressChanged)


    int linksCount() const;
    void setLinksCount(int a_linksCount);

    int activeLinksCount() const;
    void setActiveLinksCount(int a_count);

    QString nodeAddress() const;
    void setNodeAddress(const QString &a_nodeAddress);

    QString name() const;
    void setName(const QString &a_name);

    State state() const;
    QString stateRepresentation() const;
    void setState(State a_state);
    void setProperties(QVariantMap a_stateMap);

    State targetState() const;
    QString targetStateRepresentation() const;
    void setTargetState(State a_targetState);

    static State toState(QString a_stateRepresentation);

signals:
    void nameChanged(const QString& a_name);

    QString stateChanged(State a_state);
    QString stateRepresentationChanged(const QString& a_state);

    QString targetStateChanged(State a_state);
    QString targetStateRepresentationChanged(const QString& a_targetState);

    void activeLinksCountChanged(int a_count);
    void linksCountChanged(int a_count);
    void nodeAddressChanged(const QString& a_nodeAddress);

private:
    static QString toRepresentation(State a_state);


    QString m_name;
    State m_state {};
    State m_targetState {};

    int m_linksCount{};
    int m_activeLinksCount{};
    QString m_nodeAddress;

    static const QMap<QString, State> s_stateStrings;
    static const QMap<State, QString> s_stateRepresentations;
};

Q_DECLARE_METATYPE(DapNetwork::State)

#endif // DAPNETWORK_H
