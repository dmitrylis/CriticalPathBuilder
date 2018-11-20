#include "CpbStory.h"
#include "CpbSprint.h"

using namespace CPB;

Story::Story(const QString& title, Sprint* parentSprint)
    : QObject(parentSprint),
      m_parentSprint(parentSprint),
      m_title(title),
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

int Story::row() const
{
    return m_row;
}

TaskModel* Story::taskModel() const
{
    return m_taskModel;
}
