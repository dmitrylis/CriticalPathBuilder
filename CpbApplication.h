#ifndef CPBAPPLICATION_H
#define CPBAPPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "CpbSprintManager.h"
#include "CpbStoryManager.h"
#include "CpbTaskManager.h"
#include "CpbPopupManager.h"
#include "CpbXmlSerializer.h"

class QQmlContext;

namespace CPB {

class Application : public QGuiApplication
{
    Q_OBJECT
public:
    Application(int &argc, char **argv, int flags = ApplicationFlags);
    ~Application();

    void registerTypes() const;
    void createBindings() const;
    void loadResources() const;
    void setContextProperties(const QQmlApplicationEngine& engine);

private:
    SprintManager m_sprintManager;
    StoryManager m_storyManager;
    TaskManager m_taskManager;
    PopupManager m_popupManager;
    XmlSerializer m_xmlSerializer;
};

}

#endif // CPBAPPLICATION_H
