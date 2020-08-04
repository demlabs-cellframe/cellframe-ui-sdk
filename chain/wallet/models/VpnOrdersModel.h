#ifndef VPNORDERSMODEL_H
#define VPNORDERSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <algorithm>

#include "VpnOrder.h"

class VpnOrdersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_PROPERTY(SortType sortType READ sortType WRITE setSortType NOTIFY sortTypeChanged)

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
        speedLimitDisplayRole
    };

    enum SortType
    {
        SortByRegion,
        SortByToken
    };
    Q_ENUM(SortType);

    static VpnOrdersModel *getInstance();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;    
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    SortType sortType();
    void setSortType(SortType type);
private:
    static VpnOrdersModel* m_instance;

    QList <VpnOrder> m_vpnOrders;

    SortType m_sortType;

    explicit VpnOrdersModel(QObject *parent = nullptr);
signals:
    void sortTypeChanged(SortType);
};

#endif // VPNORDERSMODEL_H
