#include "CpbStoryModel.h"

using namespace CPB;

StoryModel::StoryModel(QObject *parent)
    : EntityModel<Story> (parent)
{
}

StoryModel::~StoryModel()
{
}

QVariant StoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    Story* const story = m_entityList[index.row()];
    switch(role) {
    case StoryRoles::StoryRole:
        return QVariant::fromValue(story);
    case StoryRoles::TitleRole:
        return story->title();
    case StoryRoles::OwnerRole:
        return story->owner();
    case StoryRoles::RowCountRole:
        return story->rowCount();
    case StoryRoles::ColumnCountRole:
        return story->columnCount();
    case StoryRoles::TaskModelRole:
        return QVariant::fromValue(story->taskModel());
    default:
        break;
    }

    return QVariant();
}

bool StoryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    Story* const story = m_entityList[index.row()];
    switch(role) {
    case StoryRoles::OwnerRole:
        story->setOwner(value.toString());
        break;
    case StoryRoles::RowCountRole:
        story->setRowCount(value.toInt());
        break;
    default:
        QAbstractListModel::setData(index, value, role);
        break;
    }

    return true;
}

QHash<int, QByteArray> StoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StoryRoles::StoryRole] = "storyRole";
    roles[StoryRoles::TitleRole] = "titleRole";
    roles[StoryRoles::OwnerRole] = "ownerRole";
    roles[StoryRoles::RowCountRole] = "rowCountRole";
    roles[StoryRoles::ColumnCountRole] = "columnCountRole";
    roles[StoryRoles::TaskModelRole] = "taskModelRole";
    return roles;
}
