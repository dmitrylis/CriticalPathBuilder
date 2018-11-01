#include "CpbStoryModel.h"

using namespace CPB;
using namespace std;

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
    roles[StoryRoles::RowRole] = "rowRole";
    roles[StoryRoles::TaskModelRole] = "taskModelRole";
    return roles;
}

bool StoryModel::move(int first, int last)
{
    if(first!=last)
    {
        if (first < last)
        {
            swap(first, last);
        }
        emit beginMoveRows(QModelIndex(), first, first, QModelIndex(), last);
        mStoryList.swap(first, last);
        emit endMoveRows();
    }

    return true;
}

bool StoryModel::append(Story *story)
{
    if (story == nullptr || mStoryList.contains(story))
    {
        return false;
    }

    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mStoryList.append(story);
    emit endInsertRows();

    return true;
}

bool StoryModel::remove(Story *story)
{
    if (story == nullptr)
    {
        return false;
    }

    const int storyIndex = mStoryList.indexOf(story);
    if (storyIndex < 0)
    {
        return false;
    }

    emit beginRemoveRows(QModelIndex(), storyIndex, storyIndex);
    mStoryList.removeAt(storyIndex);
    emit endRemoveRows();

    return true;
}

Story *StoryModel::getPrevious(Story *sprint) const
{
    if (sprint == nullptr)
    {
        return nullptr;
    }

    int sprintIndex = mStoryList.indexOf(sprint) - 1;
    if (isValidIndex(sprintIndex))
    {
        return mStoryList[sprintIndex];
    }

    return nullptr;
}

Story *StoryModel::getNext(Story *sprint) const
{
    if (sprint == nullptr)
    {
        return nullptr;
    }

    int sprintIndex = mStoryList.indexOf(sprint) + 1;
    if (isValidIndex(sprintIndex))
    {
        return mStoryList[sprintIndex];
    }

    return nullptr;
}

bool StoryModel::isValidIndex(int index) const
{
    return 0 <= index && index < rowCount();
}
