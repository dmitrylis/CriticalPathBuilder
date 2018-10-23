#include "CpbTaskModel.h"

using namespace CPB;

TaskModel::TaskModel(QObject *parent): QAbstractListModel(parent)
{

}

QVariant TaskModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
    {
        return 0;
    }

    return mTaskList.count();
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
        return mTaskList[index.row()]->title();
    case TaskRoles::ParentStoryRole:
        return mTaskList[index.row()]->title();
    case TaskRoles::RowRole:
        return mTaskList[index.row()]->title();
    case TaskRoles::ColumnRole:
        return mTaskList[index.row()]->title();
    case TaskRoles::DaysRole:
        return mTaskList[index.row()]->title();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TaskRoles::TitleRole] = "titleRole";
    roles[TaskRoles::ParentStoryRole] = "ParentStoryRole";
    roles[TaskRoles::RowRole] = "RowRole";
    roles[TaskRoles::ColumnRole] = "ColumnRole";
    roles[TaskRoles::DaysRole] = "DaysRole";
    return roles;
}
