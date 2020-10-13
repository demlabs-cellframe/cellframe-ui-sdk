#ifndef DAPNETWORKSLIST_H
#define DAPNETWORKSLIST_H

#include <QAbstractListModel>
#include <DapNetwork.h>

class DapNetworksList: public QObject
{
    Q_OBJECT
public:

    DapNetworksList(QObject *a_parrent = nullptr);


    QList<QObject*> model();

    DapNetwork* findNetwork(const QString& a_name);

public slots:
    void fill(QVariant a_stringList);

private:
    QList<DapNetwork*> m_networks;
};

#endif // DAPNETWORKSMODEL_H
