#include "CpbStory.h"
#include "CpbSprint.h"

using namespace CPB;

Story::Story(const QString& title, Sprint* parentSprint)
    : QObject(parentSprint),
      m_parentSprint(parentSprint),
      m_title(title),
      m_rowCount(1),
      m_columnCount(parentSprint->daysCount()),
      m_taskModel(nullptr)
{
    m_taskModel = new TaskModel(this);
}

Story::~Story()
{
}

Sprint* Story::parentSprint() const
{
    return m_parentSprint;
}

QString Story::title() const
{
    return m_title;
}

int Story::rowCount() const
{
    return m_rowCount;
}

int Story::columnCount() const
{
    return m_columnCount;
}

TaskModel* Story::taskModel() const
{
    return m_taskModel;
}

void Story::setRowCount(int rowCount)
{
    m_rowCount = rowCount;
}
