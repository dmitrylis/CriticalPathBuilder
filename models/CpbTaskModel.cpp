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

    Task* const task = m_entityList[index.row()];
    switch( role ) {
    case TaskRoles::TitleRole:
        return task->title();
    case TaskRoles::RowRole:
        return task->row();
    case TaskRoles::ColumnRole:
        return task->column();
    case TaskRoles::DaysRole:
        return task->title(); // TODO: need to update it
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
