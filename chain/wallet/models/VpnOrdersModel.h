#ifndef VPNORDERSMODEL_H
#define VPNORDERSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <algorithm>
#include <QList>

#include "VpnOrder.h"

class VpnOrdersModel : public QAbstractListModel
{
    Q_OBJECT

    QList <VpnOrder> m_aOrders;

    explicit VpnOrdersModel(QObject *parent = nullptr);

public:
    Q_INVOKABLE void sortByToken();
    Q_INVOKABLE void sortByRegion();

    enum VpnOrderRole
    {
        nameDisplayRole = Qt::UserRole,
        regionDisplayRole,
        switchedOnDisplayRole,
        unitsDisplayRole,
        unitsTypeDisplayRole,
        valueDisplayRole,
        tokenDisplayRole,
        unsafeDisplayRole,
        speedLimitDisplayRole,
    };

    static VpnOrdersModel *getInstance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;    

    QHash<int, QByteArray> roleNames() const override;
};

#endif // VPNORDERSMODEL_H
