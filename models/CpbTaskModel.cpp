#include "CpbTaskModel.h"

using namespace CPB;

TaskModel::TaskModel(QObject *parent)
    : EntityModel<Task> (parent)
{
}

TaskModel::~TaskModel()
{
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    QVariant aData;
    switch( role ) {
    case TaskRoles::TitleRole:
        return m_entityList[index.row()]->title();
    case TaskRoles::RowRole:
        return m_entityList[index.row()]->title();
    case TaskRoles::ColumnRole:
        return m_entityList[index.row()]->title();
    case TaskRoles::DaysRole:
        return m_entityList[index.row()]->title();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TaskRoles::TitleRole] = "titleRole";
    roles[TaskRoles::RowRole] = "rowRole";
    roles[TaskRoles::ColumnRole] = "columnRole";
    roles[TaskRoles::DaysRole] = "daysRole";
    return roles;
}
