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

PopupManager::PopupManager(QObject *parent) : BasePopupManager(parent)
{
}

PopupManager::~PopupManager()
{
}

void PopupManager::showCreateSprintPopup()
{
    show(CREATE_SPRINT_POPUP);
}

void PopupManager::showCreateStoryPopup(const QVariant& parentSprint)
{
    show(CREATE_STORY_POPUP, QVariantList() << parentSprint);
}

void PopupManager::showCreateTaskPopup(const QVariant& parentStory, int row, int column)
{
    show(CREATE_TASK_POPUP, QVariantList() << parentStory << row << column);
}

void PopupManager::showRemoveSprintPopup(const QVariant& sprintToRemove)
{
    show(REMOVE_SPRINT_POPUP, QVariantList() << sprintToRemove);
}

void PopupManager::showRemoveStoryPopup(const QVariant &storyToRemove)
{
    show(REMOVE_STORY_POPUP, QVariantList() << storyToRemove);
}

void PopupManager::showRemoveTaskPopup(const QVariant& taskToRemove)
{
    show(REMOVE_TASK_POPUP, QVariantList() << taskToRemove);
}
