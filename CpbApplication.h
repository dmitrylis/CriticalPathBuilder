#ifndef CPBAPPLICATION_H
#define CPBAPPLICATION_H

#include <QGuiApplication>

class QQmlApplicationEngine;

namespace CPB {

class GlobalManager;
class SprintManager;
class StoryManager;
class TaskManager;
class UserManager;
class PopupManager;
class TooltipManager;
class ThemeManager;
class XmlSerializer;

class Application : public QGuiApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv, int flags = ApplicationFlags);
    ~Application();

    void initialize(QQmlApplicationEngine *engine);

protected:
    void createObjects(QQmlApplicationEngine *engine);
    void registerTypes() const;
    void createBindings() const;
    void loadResources() const;
    void setContextProperties();

private:
    QQmlApplicationEngine *m_engine {nullptr};

    GlobalManager *m_globalManager {nullptr};
    SprintManager *m_sprintManager {nullptr};
    StoryManager *m_storyManager {nullptr};
    TaskManager *m_taskManager {nullptr};
    UserManager *m_userManager {nullptr};
    PopupManager *m_popupManager {nullptr};
    TooltipManager *m_tooltipManager {nullptr};
    ThemeManager *m_themeManager {nullptr};
    XmlSerializer *m_xmlSerializer {nullptr};
};

}

#endif // CPBAPPLICATION_H
