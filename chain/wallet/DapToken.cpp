#include "DapToken.h"

QMap<QString , DapToken*> DapToken::s_tokens;


DapToken::DapToken(QObject *parent)
    : QObject(parent)
{
}

DapToken::DapToken(const QString &a_name, QObject *parent)
    : QObject(parent)
    , m_name(a_name)
{
}

QString DapToken::name() const
{
    return m_name;
}

void DapToken::setName(const QString &a_name)
{
    if (m_name == a_name)
        return;

    m_name = a_name;
    emit this->nameChanged(a_name);
}

const DapToken *DapToken::token(const QString &a_name)
{
    if (!s_tokens.contains(a_name))
    {
        // TODO: Removing objects.
        //DapTokensModel
        DapToken* newToken = new DapToken(a_name);
        s_tokens.insert(a_name, newToken);
        return newToken;
    }
    else
        return s_tokens.value(a_name);
}

bool DapToken::operator<(const DapToken &a_another)
{
    return this->name() < a_another.name();
}
