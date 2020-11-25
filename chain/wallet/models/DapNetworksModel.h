#ifndef DAPNETWORKSMODEL_H
#define DAPNETWORKSMODEL_H

#include <QAbstractListModel>

class DapNetwork;

class DapNetworksModel : public QAbstractListModel
{
    Q_OBJECT

    enum Roles
    {
        NETWORK = Qt::UserRole,
    };
public:

    DapNetworksModel();

    DapNetwork* find(const QString& a_name);

    DapNetwork* addIfNotExist(const QString& a_name, bool *a_wasCreated = nullptr);

    QStringList names();
    const QList<DapNetwork *>& all() const;
    bool isEmpty() const;

    Q_INVOKABLE void append(DapNetwork* a_network);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:

    QList<DapNetwork*> m_networks;
};

#endif // DAPNETWORKSMODEL_H
