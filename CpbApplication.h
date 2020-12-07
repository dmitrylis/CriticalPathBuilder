#ifndef CPBAPPLICATION_H
#define CPBAPPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "CpbGlobalManager.h"
#include "CpbSprintManager.h"
#include "CpbStoryManager.h"
#include "CpbTaskManager.h"
#include "CpbUserManager.h"
#include "CpbPopupManager.h"
#include "CpbTooltipManager.h"
#include "CpbXmlSerializer.h"

class QQmlContext;

namespace CPB {

class Application : public QGuiApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv, int flags = ApplicationFlags);
    ~Application();

    void registerTypes() const;
    void createBindings() const;
    void loadResources() const;
    void setContextProperties(const QQmlApplicationEngine& engine);

private:
    GlobalManager m_globalManager;
    SprintManager m_sprintManager;
    StoryManager m_storyManager;
    TaskManager m_taskManager;
    UserManager m_userManager;
    PopupManager m_popupManager;
    TooltipManager m_tooltipManager;
    XmlSerializer m_xmlSerializer;
};

}

#endif // CPBAPPLICATION_H
