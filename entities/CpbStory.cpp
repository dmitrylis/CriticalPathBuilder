#include "CpbStory.h"

using namespace CPB;

Story::Story(const QString& title, QObject *parent)
    : QObject(parent),
      m_title(title),
      m_taskModel(nullptr)
{
    m_taskModel = new TaskModel(this);
}

Story::~Story()
{
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
