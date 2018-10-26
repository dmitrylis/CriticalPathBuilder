#include "CpbSprintModel.h"

using namespace CPB;

SprintModel::SprintModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant SprintModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

int SprintModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
    {
        return 0;
    }

    return mSprintList.count();
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
        return QVariant::fromValue(mSprintList[index.row()]);
    case SprintRoles::TitleRole:
        return mSprintList[index.row()]->title();
    case SprintRoles::StartDateRole:
        return mSprintList[index.row()]->title();
    case SprintRoles::EndDateRole:
        return mSprintList[index.row()]->title();
    case SprintRoles::StoryModelRole:
        return mSprintList[index.row()]->title();
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

bool SprintModel::append(Sprint *sprint)
{
    if (sprint == nullptr || mSprintList.contains(sprint))
    {
        return false;
    }

    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mSprintList.append(sprint);
    emit endInsertRows();

    return true;
}

bool SprintModel::remove(Sprint *sprint)
{
    if (sprint == nullptr)
    {
        return false;
    }

    const int sprintIndex = mSprintList.indexOf(sprint);
    if (sprintIndex < 0)
    {
        return false;
    }

    emit beginRemoveRows(QModelIndex(), sprintIndex, sprintIndex);
    mSprintList.removeAt(sprintIndex);
    emit endRemoveRows();

    return true;
}

Sprint *SprintModel::getPrevious(Sprint *sprint) const
{
    if (sprint == nullptr)
    {
        return nullptr;
    }

    int sprintIndex = mSprintList.indexOf(sprint) - 1;
    if (isValidIndex(sprintIndex))
    {
        return mSprintList[sprintIndex];
    }

    return nullptr;
}

Sprint *SprintModel::getNext(Sprint *sprint) const
{
    if (sprint == nullptr)
    {
        return nullptr;
    }

    int sprintIndex = mSprintList.indexOf(sprint) + 1;
    if (isValidIndex(sprintIndex))
    {
        return mSprintList[sprintIndex];
    }

    return nullptr;
}

bool SprintModel::isValidIndex(int index) const
{
    return 0 <= index && index < rowCount();
}
