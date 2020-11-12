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
    explicit DapTokenValue (QObject* a_parent = nullptr) : QObject(a_parent){}
    explicit DapTokenValue(DapToken* a_token, balance_t a_amount, QObject *a_parent = nullptr);
    DapTokenValue(const DapTokenValue& a_token);
    DapTokenValue& operator=(const DapTokenValue& a_token);

    DapToken* token()  const { return m_token;  }
    balance_t amount() const { return m_amount; }
    Q_INVOKABLE QString representation() const { return QString::number(m_amount) + " " + m_token->name(); }

    void setToken(DapToken *a_token);
    void setAmount(balance_t a_amount);

signals:
    void tokenChanged(DapToken*);
    void amountChanged(balance_t);

private:
    DapToken* m_token = nullptr;
    balance_t m_amount{};
};

#endif // DAPTOKENVALUE_H
