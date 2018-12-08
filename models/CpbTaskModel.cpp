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
    case TaskRoles::TaskRole:
        return QVariant::fromValue(task);
    case TaskRoles::TitleRole:
        return task->title();
    case TaskRoles::RowRole:
        return task->row();
    case TaskRoles::ColumnRole:
        return task->column();
    case TaskRoles::DaysCountRole:
        return task->daysCount();
    default:
        break;
    }

    return QVariant();
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    Task* const task = m_entityList[index.row()];
    switch(role) {
    case TaskRoles::RowRole:
        task->setRow(value.toInt());
        break;
    case TaskRoles::ColumnRole:
        task->setColumn(value.toInt());
        break;
    case TaskRoles::DaysCountRole:
        task->setDaysCount(value.toInt());
        break;
    default:
        QAbstractListModel::setData(index, value, role);
        break;
    }

    return true;
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TaskRoles::TaskRole] = "taskRole";
    roles[TaskRoles::TitleRole] = "titleRole";
    roles[TaskRoles::RowRole] = "rowRole";
    roles[TaskRoles::ColumnRole] = "columnRole";
    roles[TaskRoles::DaysCountRole] = "daysCountRole";
    return roles;
}

Task* TaskModel::task(int row, int column) const
{
    // need to check row and column

    // check that row and column are placed inside of task body
    auto result = std::find_if(m_entityList.begin(), m_entityList.end(), [row, column] (const Task* const task) {
        return task->row() <= row && row < task->row() + 1 &&
                task->column() <= column && column < task->column() + task->daysCount();
    });

    return (result != m_entityList.end()) ? *result : nullptr;
}

int TaskModel::maxRow() const
{
    int maxRow = 0;

    std::for_each(m_entityList.begin(), m_entityList.end(), [&maxRow] (const Task* const task) {
        const int row = task->row();
        if (row > maxRow)
        {
            maxRow = row;
        }
    });

    return maxRow;
}
