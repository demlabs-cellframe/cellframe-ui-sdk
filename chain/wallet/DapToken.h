#ifndef DAPTOKEN_H
#define DAPTOKEN_H

#include <QObject>
#include <QMap>

class DapToken : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit DapToken(const QString& a_name, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &a_name);

    static const DapToken *token(const QString& a_name);

    bool operator<(const DapToken& a_another);

signals:
    void nameChanged(const QString& a_name);

private:
    QString m_name;

    static QMap<QString , DapToken*> s_tokens;
};


#endif // DAPTOKEN_H
