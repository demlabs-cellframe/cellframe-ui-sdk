#ifndef DAPTOKENVALUE_H
#define DAPTOKENVALUE_H

#include <QObject>
#include <DapToken.h>

typedef unsigned __int128 balance_t;

#define DATOSHI_EXP 9
#define DATOSHI_KOEF  pow(10, DATOSHI_EXP)


class DapTokenValue : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DapToken* token READ token WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(QString amountString READ amountString NOTIFY amountStringChanged)
    Q_PROPERTY(QString representation READ representation NOTIFY representationChanged)

public:

    explicit DapTokenValue (QObject* a_parent = nullptr) : QObject(a_parent){}
    explicit DapTokenValue(const DapToken* a_token, balance_t a_amount, QObject *a_parent = nullptr);
    DapTokenValue(const DapTokenValue& a_token);
    DapTokenValue& operator=(const DapTokenValue& a_token);

    DapToken* token()  const { return const_cast<DapToken*>(m_token); }
    balance_t amount() const { return m_amount; }
    QString amountString() const;

    Q_INVOKABLE QString representation() const;

    void setToken(DapToken *a_token);
    void setAmount(balance_t a_amount);

    static QString datoshiAmountToString(balance_t a_amount);
    static balance_t datoshiStringtoTokensAmount(QString a_datoshiAmount);
    static balance_t tokensAmountStringtoTokensAmount(const QString &a_tokensAmount);

signals:
    void tokenChanged(DapToken*);
    void amountChanged(balance_t);
    void amountStringChanged(const QString& a_amountString);
    void representationChanged(const QString& a_representation);

private:
    const DapToken* m_token = nullptr;
    balance_t m_amount{};
};

#endif // DAPTOKENVALUE_H
