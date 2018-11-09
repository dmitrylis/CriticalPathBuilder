#include "CpbSprintModel.h"

using namespace CPB;

SprintModel::SprintModel(QObject *parent)
    : EntityModel<Sprint> (parent)
{
}

SprintModel::~SprintModel()
{
}

QVariant SprintModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    QVariant aData;
    switch( role ) {
    case SprintRoles::SprintRole:
        return QVariant::fromValue(m_entityList[index.row()]);
    case SprintRoles::TitleRole:
        return m_entityList[index.row()]->title();
    case SprintRoles::StartDateRole:
        return m_entityList[index.row()]->title();
    case SprintRoles::EndDateRole:
        return m_entityList[index.row()]->title();
    case SprintRoles::StoryModelRole:
        return m_entityList[index.row()]->title();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> SprintModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SprintRoles::SprintRole] = "sprintRole";
    roles[SprintRoles::TitleRole] = "titleRole";
    roles[SprintRoles::StartDateRole] = "startDateRole";
    roles[SprintRoles::EndDateRole] = "endDateRole";
    roles[SprintRoles::StoryModelRole] = "storyModelRole";
    return roles;
}

Sprint *SprintModel::getPrevious(Sprint *sprint) const
{
    if (sprint == nullptr || !m_entityList.contains(sprint))
    {
        return nullptr;
    }

    int sprintIndex = m_entityList.indexOf(sprint) - 1;
    if (isValidIndex(sprintIndex))
    {
        return m_entityList[sprintIndex];
    }

    return nullptr;
}

Sprint *SprintModel::getNext(Sprint *sprint) const
{
    if (sprint == nullptr || !m_entityList.contains(sprint))
    {
        return nullptr;
    }

    int sprintIndex = m_entityList.indexOf(sprint) + 1;
    if (isValidIndex(sprintIndex))
    {
        return m_entityList[sprintIndex];
    }

    return nullptr;
}

bool SprintModel::isValidIndex(int index) const
{
    return 0 <= index && index < rowCount();
}
