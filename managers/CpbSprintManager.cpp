#include "CpbSprintManager.h"

using namespace CPB;

namespace  {
const QString SPRINT_NAME_TEMPLATE ("Sprint %0");
}

SprintManager::SprintManager(QObject *parent) :
    QObject(parent),
    m_sprintModel(nullptr),
    m_currentSprint(nullptr)
{
    m_sprintModel = new SprintModel(this);
}

SprintModel *SprintManager::sprintModel() const
{
    return m_sprintModel;
}

Sprint* SprintManager::currentSprint() const
{
    return m_currentSprint;
}

void SprintManager::setCurrentSprint(Sprint* sprint)
{
    if (m_currentSprint == sprint)
    {
        return;
    }

    m_currentSprint = sprint;
    emit currentSprintChanged(m_currentSprint);
}

void SprintManager::addSprint()
{
    // >> TODO: move to separate class?
    int sprintNumber = 1;
    QString newSprintName = SPRINT_NAME_TEMPLATE.arg(sprintNumber), tempSprintName;

    while (sprintNumber <= (m_sprintModel->rowCount() + 1))
    {
        tempSprintName = SPRINT_NAME_TEMPLATE.arg(sprintNumber);
        if (m_sprintModel->isNameValid(tempSprintName))
        {
            newSprintName = tempSprintName;
            break;
        }
        ++sprintNumber;
    }
    // <<

    Sprint* newSprint = new Sprint(newSprintName, this);

    if (m_sprintModel->append(newSprint))
    {
        setCurrentSprint(newSprint);
    }
    else
    {
        newSprint->deleteLater();
    }
}

void SprintManager::removeSprint(Sprint* sprint)
{
    // detect sprint to select after removing
    Sprint* sprintToSelect = currentSprint();
    if (sprintToSelect == sprint)
    {
        sprintToSelect = m_sprintModel->getPrevious(sprint);
        if (sprintToSelect == nullptr)
        {
            sprintToSelect = m_sprintModel->getNext(sprint);
        }
    }

    // remove sprint and select detected
    if (m_sprintModel->remove(sprint))
    {
        setCurrentSprint(sprintToSelect);
        sprint->deleteLater();
    }
}
