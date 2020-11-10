#ifndef DAPTOKENVALUE_H
#define DAPTOKENVALUE_H

#include <QObject>
#include <DapToken.h>
#include <DapBalanceModel.h>

class DapTokenValue : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DapToken* token READ token WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(balance_t amount READ amount WRITE setAmount NOTIFY amountChanged)

public:
    Q_INVOKABLE explicit DapTokenValue (QObject* a_parent = nullptr) : QObject(a_parent){}
    Q_INVOKABLE explicit DapTokenValue(DapToken* a_token, balance_t a_amount, QObject *a_parent = nullptr);

    Q_INVOKABLE DapToken* token()  const { return m_token; }
    Q_INVOKABLE balance_t amount() const { return m_amount; }
    Q_INVOKABLE QString representation() { return QString::number(m_amount) + " " + m_token->name(); }

    Q_INVOKABLE void setToken(DapToken* a_token);
    Q_INVOKABLE void setAmount(balance_t a_amount);

signals:
    void tokenChanged(DapToken*);
    void amountChanged(balance_t);

private:
    DapToken* m_token{Q_NULLPTR};
    balance_t m_amount{};
};
//Q_DECLARE_METATYPE (DapTokenValue)
#endif // DAPTOKENVALUE_H
