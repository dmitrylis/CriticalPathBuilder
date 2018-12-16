#include "CpbTask.h"
#include "CpbStory.h"

using namespace CPB;

Task::Task(Story* parentStory, const QString& title, const QString& owner, TaskType type, int row, int column)
    : QObject(parentStory),
      m_parentStory(parentStory),
      m_title(title),
      m_owner(owner),
      m_type(type),
      m_row(row),
      m_column(column),
      m_daysCount(1)
{
}

Task::~Task()
{
}

Story* Task::parentStory() const
{
    return m_parentStory;
}

QString Task::title() const
{
    return m_title;
}

QString Task::owner() const
{
    return m_owner;
}

Task::TaskType Task::type() const
{
    return m_type;
}

int Task::row() const
{
    return m_row;
}

int Task::column() const
{
    return m_column;
}

int Task::daysCount() const
{
    return m_daysCount;
}

void Task::setOwner(const QString &owner)
{
    m_owner = owner;
}

void Task::setType(TaskType type)
{
    m_type = type;
}

void Task::setRow(int row)
{
    m_row = row;
}

void Task::setColumn(int column)
{
    m_column = column;
}

void Task::setDaysCount(int daysCount)
{
    m_daysCount = daysCount;
}
