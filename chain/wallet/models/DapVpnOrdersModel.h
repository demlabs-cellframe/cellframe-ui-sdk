#ifndef DAPVPNORDERSMODEL_H
#define DAPVPNORDERSMODEL_H

#include <QAbstractListModel>
#include <algorithm>
#include <QList>
#include "DapVpnOrder.h"

class DapVpnOrdersModel: public QAbstractListModel
{
    Q_OBJECT
    explicit DapVpnOrdersModel(QObject *parent = Q_NULLPTR);

public:
    enum DapVpnOrdersRoles {
        NameDisplayRole = Qt::UserRole,
        DateDisplayRole,
        UnitsDisplayRole,
        TypeDisplayRole,
        ValueDisplayRole,
        TokenDisplayRole
    };
    Q_ENUM(DapVpnOrdersRoles)

    static DapVpnOrdersModel& instance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void append(const DapVpnOrder& a_order);

private:
    QList<DapVpnOrder> m_orders;
};

#endif // DAPVPNORDERSMODEL_H
