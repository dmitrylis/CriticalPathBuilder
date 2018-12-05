#include "CpbPopupManager.h"

using namespace CPB;

namespace  {
const QString CREATE_SPRINT_POPUP ("qrc:/qml/popups/CpbCreateSprintPopup.qml");
const QString CREATE_STORY_POPUP ("qrc:/qml/popups/CpbCreateStoryPopup.qml");
const QString CREATE_TASK_POPUP ("qrc:/qml/popups/CpbCreateTaskPopup.qml");
const QString REMOVE_SPRINT_POPUP ("qrc:/qml/popups/CpbRemoveSprintPopup.qml");
const QString REMOVE_STORY_POPUP ("qrc:/qml/popups/CpbRemoveStoryPopup.qml");
const QString REMOVE_TASK_POPUP ("qrc:/qml/popups/CpbRemoveTaskPopup.qml");
}

PopupManager::PopupManager(QObject *parent) : QObject(parent)
{
}

PopupManager::~PopupManager()
{
}

QString PopupManager::popupPath() const
{
    return m_popupPath;
}

QVariantList PopupManager::popupData() const
{
    return m_popupData;
}

void PopupManager::showPopup(const QString& popupPath, const QVariantList& popupData)
{
    bool updateNeeded = false;

    if (m_popupPath != popupPath)
    {
        m_popupPath = popupPath;
        updateNeeded = true;
    }

    if (m_popupData != popupData)
    {
        m_popupData = popupData;
        updateNeeded = true;
    }

    if (updateNeeded)
    {
        emit popupChanged();
    }
}

void PopupManager::showCreateSprintPopup()
{
    showPopup(CREATE_SPRINT_POPUP);
}

void PopupManager::showCreateStoryPopup(const QVariant& parentSprint)
{
    showPopup(CREATE_STORY_POPUP, QVariantList() << parentSprint);
}

void PopupManager::showCreateTaskPopup(int row, int column, const QVariant& parentStory)
{
    showPopup(CREATE_TASK_POPUP, QVariantList() << row << column << parentStory);
}

void PopupManager::showRemoveSprintPopup(const QVariant& sprintToRemove)
{
    showPopup(REMOVE_SPRINT_POPUP, QVariantList() << sprintToRemove);
}

void PopupManager::showRemoveStoryPopup(const QVariant &storyToRemove)
{
    showPopup(REMOVE_STORY_POPUP, QVariantList() << storyToRemove);
}

void PopupManager::showRemoveTaskPopup(const QVariant& taskToRemove)
{
    showPopup(REMOVE_TASK_POPUP, QVariantList() << taskToRemove);
}

void PopupManager::hidePopup()
{
    showPopup("");
}
