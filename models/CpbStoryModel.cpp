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
    case StoryRoles::RowRole:
        return story->row();
    case StoryRoles::TaskModelRole:
        return QVariant::fromValue(story->taskModel());
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> StoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StoryRoles::StoryRole] = "storyRole";
    roles[StoryRoles::TitleRole] = "titleRole";
    roles[StoryRoles::RowRole] = "rowRole";
    roles[StoryRoles::TaskModelRole] = "taskModelRole";
    return roles;
}
