#include "CpbStory.h"
#include "CpbSprint.h"

using namespace CPB;

Story::Story(Sprint* parentSprint, const QString& title, const QString& owner)
    : QObject(parentSprint),
      m_parentSprint(parentSprint),
      m_title(title),
      m_owner(owner),
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

QString Story::owner() const
{
    return m_owner;
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

void Story::setOwner(const QString &owner)
{
    m_owner = owner;
}

void Story::setRowCount(int rowCount)
{
    m_rowCount = rowCount;
}
