#include "CpbTask.h"
#include "CpbStory.h"

using namespace CPB;

Task::Task(Story* parentStory, const QString& title, const QString& owner, int row, int column)
    : QObject(parentStory),
      m_parentStory(parentStory),
      m_title(title),
      m_owner(owner),
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
