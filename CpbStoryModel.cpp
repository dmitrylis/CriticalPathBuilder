#include "CpbStoryModel.h"

using namespace CPB;

StoryModel::StoryModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

QVariant StoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

int StoryModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
    {
        return 0;
    }

    return mStoryList.count();
}

QVariant StoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    QVariant aData;
    switch( role ) {
    case StoryRoles::TitleRole:
        return mStoryList[index.row()]->title();
    case StoryRoles::ParentSprintRole:
        return mStoryList[index.row()]->title();
    case StoryRoles::RowRole:
        return mStoryList[index.row()]->title();
    case StoryRoles::TaskModelRole:
        return mStoryList[index.row()]->title();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> StoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StoryRoles::TitleRole] = "titleRole";
    roles[StoryRoles::ParentSprintRole] = "ParentSprintRole";
    roles[StoryRoles::RowRole] = "RowRole";
    roles[StoryRoles::TaskModelRole] = "TaskModelRole";
    return roles;
}
