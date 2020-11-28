#include "CpbSprintManager.h"

#include "CpbUtils.h"

using namespace CPB;

namespace  {
const QString SPRINT_TITLE_TEMPLATE ("Sprint %0");
}

SprintManager::SprintManager(QObject *parent) :
    QObject(parent),
    m_sprintModel(nullptr),
    m_currentSprint(nullptr)
{
    m_sprintModel = new SprintModel(this);
}

SprintManager::~SprintManager()
{
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

QString SprintManager::newSprintName() const
{
    return Utils::generateEntityName<SprintModel>(SPRINT_TITLE_TEMPLATE, sprintModel());
}

void SprintManager::createSprint(const QString& sprintTitle, const QDate& startDate, const QDate& endDate)
{
    if (sprintTitle.isNull() || sprintTitle.isEmpty())
    {
        return;
    }

    Sprint* newSprint = new Sprint(sprintTitle, startDate, endDate, this);
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
