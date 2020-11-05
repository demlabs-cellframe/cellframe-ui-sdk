#ifndef DAPNETWORKSLIST_H
#define DAPNETWORKSLIST_H

#include <QAbstractListModel>
#include <DapNetwork.h>

class DapNetworksList: public QObject
{
    Q_OBJECT
public:

    DapNetworksList(QObject *a_parrent = nullptr);

    Q_INVOKABLE QList<QObject*> model();

    DapNetwork* findNetwork(const QString& a_name);
    DapNetwork* addIfNotExist(const QString& a_name);

    void setNetworkProperties(QVariantMap a_networkState);

public slots:
    void fill(QVariant a_stringList);

signals:
    void networkAdded(DapNetwork* network);
    void modelChanged();

private:
    //If you call this method you need manually emit listCompositionChanged();
    //Not required to emit listCompositionChanged every time when network added
    DapNetwork *add(const QString& a_networkName);
    QList<DapNetwork*> m_networks;
};

#endif // DAPNETWORKSMODEL_H
