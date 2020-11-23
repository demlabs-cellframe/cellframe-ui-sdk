#ifndef DAPNETWORKSLIST_H
#define DAPNETWORKSLIST_H

#include <QAbstractListModel>
#include <DapNetwork.h>

class DapNetworksList: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> model READ model NOTIFY modelChanged)
public:

    DapNetworksList(QObject *a_parrent = nullptr);

    QList<QObject*> model();

    DapNetwork* findNetwork(const QString& a_name);
    DapNetwork* addIfNotExist(const QString& a_name);

    QStringList names();
    const QList<DapNetwork *>& all() const;
    bool isEmpty() const;

public slots:
    QList<DapNetwork*> fill(QStringList a_NetworksNames);

signals:
    void networkAdded(DapNetwork* network);
    void modelChanged(const QList<QObject*>& a_model);

private:
    //If you call this method you need manually emit listCompositionChanged();
    //Not required to emit listCompositionChanged every time when network added
    DapNetwork *add(const QString& a_networkName);
    QList<DapNetwork*> m_networks;
};

#endif // DAPNETWORKSMODEL_H
