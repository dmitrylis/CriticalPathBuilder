#include "CpbSprintManager.h"

#include <QtGlobal>

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

void SprintManager::createSprint()
{
    // >> TODO: move to separate class?
    int sprintNumber = 1;
    QString newSprintName, tempSprintName;

    while (sprintNumber <= (m_sprintModel->rowCount() + 1))
    {
        tempSprintName = SPRINT_NAME_TEMPLATE.arg(sprintNumber);
        if (m_sprintModel->titleValid(tempSprintName))
        {
            newSprintName = tempSprintName;
            break;
        }
        ++sprintNumber;
    }
    // <<

    Q_ASSERT(!newSprintName.isNull() && !newSprintName.isEmpty());

    Sprint* newSprint = new Sprint(newSprintName, this);

    if (m_sprintModel->append(newSprint))
    {
        setCurrentSprint(newSprint);
    }
    else
    {
        newSprint->deleteLater();
    }
    xmlSerializer xmldoc;
    xmldoc.xmlAddSprint(newSprintName);
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

void SprintManager::moveSprint(int from, int to)
{
    m_sprintModel->move(from, to);
}
