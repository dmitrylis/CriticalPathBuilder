#ifndef CPBPOPUPMANAGER_H
#define CPBPOPUPMANAGER_H

#include "CpbBasePopupManager.h"

namespace CPB {

class PopupManager : public BasePopupManager
{
    Q_OBJECT

public:
    explicit PopupManager(QObject *parent = nullptr);
    ~PopupManager() override;

    Q_INVOKABLE void showWelcomePopup();
    Q_INVOKABLE void showCreateSprintPopup();
    Q_INVOKABLE void showCreateStoryPopup(const QVariant& parentSprint);
    Q_INVOKABLE void showCreateTaskPopup(const QVariant& parentStory, int row, int column);
    Q_INVOKABLE void showRemoveSprintPopup(const QVariant& sprintToRemove);
    Q_INVOKABLE void showRemoveStoryPopup(const QVariant& storyToRemove);
    Q_INVOKABLE void showRemoveTaskPopup(const QVariant& taskToRemove);
};

}

#endif // CPBPOPUPMANAGER_H
