#include "CpbTask.h"
#include "CpbStory.h"

using namespace CPB;

Task::Task(const QString& title, Story* parentStory)
    : QObject(parentStory),
      m_parentStory(parentStory),
      m_title(title)
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
