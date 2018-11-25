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

    Sprint* newSprint = new Sprint(newSprintName, QDate::currentDate(), 3, this);

    if (m_sprintModel->append(newSprint))
    {
        setCurrentSprint(newSprint);
        emit sprintCreated(newSprint);
        return;
    }

    newSprint->deleteLater();
}

void SprintManager::createSprint(const QString& sprintName, const QString& startDate, const QString& endDate)
{
    Sprint* newSprint = new Sprint(sprintName,
                                   QDate::fromString(startDate, "dd.MM.yyyy"),
                                   QDate::fromString(endDate, "dd.MM.yyyy"),
                                   this);
     if (m_sprintModel->append(newSprint))
    {
        setCurrentSprint(newSprint);
        emit sprintCreated(newSprint);
        return;
    }
     newSprint->deleteLater();
}

void SprintManager::createSprint(const QString& sprintName, const QString& startDate, const qint32& duration)
{
    Sprint* newSprint = new Sprint(sprintName,
                                   QDate::fromString(startDate, "dd.MM.yyyy"),
                                   duration,
                                   this);
     if (m_sprintModel->append(newSprint))
    {
        setCurrentSprint(newSprint);
        emit sprintCreated(newSprint);
        return;
    }
     newSprint->deleteLater();
}

void SprintManager::removeSprint(Sprint* sprint)
{
    // detect sprint to select after removing
    Sprint* sprintToSelect = currentSprint();
    if (sprintToSelect == sprint)
    {
        sprintToSelect = m_sprintModel->previous(sprint);
        if (sprintToSelect == nullptr)
        {
            sprintToSelect = m_sprintModel->next(sprint);
        }
    }

    // remove sprint and select detected
    if (m_sprintModel->remove(sprint))
    {
        emit sprintRemoved(sprint->title());
        setCurrentSprint(sprintToSelect);
        sprint->deleteLater();
    }
}

void SprintManager::moveSprint(int from, int to)
{
    m_sprintModel->move(from, to);
}

void SprintManager::onModelLoaded()
{
    Sprint* sprintToSelect = m_sprintModel->first();
    if (sprintToSelect != nullptr)
    {
        setCurrentSprint(sprintToSelect);
    }
}
