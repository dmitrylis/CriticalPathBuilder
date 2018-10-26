#include "CpbSprintModel.h"

using namespace CPB;

SprintModel::SprintModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // stub
    mSprintList.append(new Sprint("Sprint 1", this));
    mSprintList.append(new Sprint("Sprint 2", this));
    mSprintList.append(new Sprint("Sprint 3", this));
    mSprintList.append(new Sprint("Sprint 4", this));
    mSprintList.append(new Sprint("Sprint 5", this));
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
    roles[SprintRoles::TitleRole] = "titleRole";
    roles[SprintRoles::StartDateRole] = "startDateRole";
    roles[SprintRoles::EndDateRole] = "endDateRole";
    roles[SprintRoles::StoryModelRole] = "storyModelRole";
    return roles;
}
