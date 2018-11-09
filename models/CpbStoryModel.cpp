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

    QVariant aData;
    switch( role ) {
    case StoryRoles::TitleRole:
        return m_entityList[index.row()]->title();
    case StoryRoles::RowRole:
        return m_entityList[index.row()]->title();
    case StoryRoles::TaskModelRole:
        return m_entityList[index.row()]->title();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> StoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StoryRoles::TitleRole] = "titleRole";
    roles[StoryRoles::RowRole] = "rowRole";
    roles[StoryRoles::TaskModelRole] = "taskModelRole";
    return roles;
}
