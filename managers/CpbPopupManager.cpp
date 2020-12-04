#include "CpbPopupManager.h"

using namespace CPB;

namespace  {
const QString WELCOME_POPUP ("qrc:/qml/popups/CpbWelcomePopup.qml");
const QString SETTINGS_POPUP ("qrc:/qml/popups/CpbSettingsPopup.qml");
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

void PopupManager::showWelcomePopup()
{
    show(WELCOME_POPUP, Policy::StrictlyModal);
}

void PopupManager::showSettingsPopup()
{
    show(SETTINGS_POPUP, Policy::PartiallyModal);
}

void PopupManager::showCreateSprintPopup()
{
    show(CREATE_SPRINT_POPUP, Policy::PartiallyModal);
}

void PopupManager::showCreateStoryPopup(const QVariant& parentSprint)
{
    show(CREATE_STORY_POPUP, Policy::PartiallyModal, QVariantList() << parentSprint);
}

void PopupManager::showCreateTaskPopup(const QVariant& parentStory, int row, int column)
{
    show(CREATE_TASK_POPUP, Policy::PartiallyModal, QVariantList() << parentStory << row << column);
}

void PopupManager::showRemoveSprintPopup(const QVariant& sprintToRemove)
{
    show(REMOVE_SPRINT_POPUP, Policy::PartiallyModal, QVariantList() << sprintToRemove);
}

void PopupManager::showRemoveStoryPopup(const QVariant &storyToRemove)
{
    show(REMOVE_STORY_POPUP, Policy::PartiallyModal, QVariantList() << storyToRemove);
}

void PopupManager::showRemoveTaskPopup(const QVariant& taskToRemove)
{
    show(REMOVE_TASK_POPUP, Policy::PartiallyModal, QVariantList() << taskToRemove);
}
