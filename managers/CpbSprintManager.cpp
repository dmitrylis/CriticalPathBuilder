#include "CpbSprintManager.h"

using namespace CPB;

SprintManager::SprintManager(QObject *parent) :
    QObject(parent),
    m_currentSprint(0)
{
    m_sprintModel = new SprintModel(this);
}

SprintModel *SprintManager::sprintModel() const
{
    return m_sprintModel;
}

int SprintManager::currentSprint() const
{
    return m_currentSprint;
}

void SprintManager::setCurrentSprint(int currentSprint)
{
    if (m_currentSprint == currentSprint)
    {
        return;
    }

    m_currentSprint = currentSprint;
    emit currentSprintChanged(m_currentSprint);
}
