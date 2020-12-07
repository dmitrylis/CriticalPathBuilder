#include "CpbUser.h"

using namespace CPB;

User::User(uint id, const QString& name, QObject *parent)
    : QObject(parent),
      m_id(id),
      m_name(name)
{
}

User::~User()
{
}

uint User::id() const
{
    return m_id;
}

QString User::name() const
{
    return m_name;
}

void User::setName(const QString &name)
{
    if (m_name == name)
    {
        m_name = name;
        emit nameChanged(name);
    }
}
