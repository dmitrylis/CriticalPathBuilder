#include "CpbTask.h"
#include "CpbStory.h"

using namespace CPB;

Task::Task(const QString& title, int row, int column, Story* parentStory)
    : QObject(parentStory),
      m_parentStory(parentStory),
      m_title(title),
      m_row(row),
      m_column(column)
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

int Task::row() const
{
    return m_row;
}

int Task::column() const
{
    return m_column;
}

int Task::setRow(int row)
{
    m_row = row;
}

int Task::setColumn(int column)
{
    m_column = column;
}
