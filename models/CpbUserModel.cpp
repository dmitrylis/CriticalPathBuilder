#include "CpbUserModel.h"

using namespace CPB;

UserModel::UserModel(QObject *parent)
    : EntityModel<User>(parent)
{
}

UserModel::~UserModel()
{
}

QVariant UserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    User* const user = m_entityList[index.row()];
    switch(role)
    {
    case UserRoles::IdRole:
        return user->id();
    case UserRoles::NameRole:
        return user->name();
    default:
        break;
    }

    return QVariant();
}

bool UserModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    User* const user = m_entityList[index.row()];
    switch(role) {
    case UserRoles::NameRole:
        user->setName(value.toString());
        break;
    default:
        QAbstractListModel::setData(index, value, role);
        break;
    }

    return true;
}

QHash<int, QByteArray> UserModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[UserRoles::IdRole] = "idRole";
    roles[UserRoles::NameRole] = "nameRole";
    return roles;
}
