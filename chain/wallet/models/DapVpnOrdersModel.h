#ifndef DAPVPNORDERSMODEL_H
#define DAPVPNORDERSMODEL_H

#include <QAbstractListModel>
#include <algorithm>
#include <QList>
#include "DapVpnOrder.h"
#include "DapTokenValue.h"

class DapVpnOrdersModel: public QAbstractListModel
{
    Q_OBJECT

public:
    enum DapVpnOrdersRoles {
        NameDisplayRole = Qt::UserRole,
        DateDisplayRole,
        UnitsDisplayRole,
        TypeDisplayRole,
        TokenValueDisplayRole
    };
    Q_ENUM(DapVpnOrdersRoles)

    explicit DapVpnOrdersModel(QObject *parent = Q_NULLPTR);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void append(DapVpnOrder *a_order);

private:
    QList<DapVpnOrder*> m_orders;
};

#endif // DAPVPNORDERSMODEL_H
