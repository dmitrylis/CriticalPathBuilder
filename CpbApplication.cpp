#include "CpbApplication.h"

#include <QMetaType>
#include <QQmlEngine>
#include <QQmlContext>

#include <QQmlApplicationEngine>
//#include <QQmlEngine>

#include "CpbGlobalManager.h"
#include "CpbSprintManager.h"
#include "CpbStoryManager.h"
#include "CpbTaskManager.h"
#include "CpbUserManager.h"
#include "CpbPopupManager.h"
#include "CpbTooltipManager.h"
#include "CpbThemeManager.h"
#include "CpbXmlSerializer.h"

using namespace CPB;

Application::Application(int &argc, char **argv, int flags)
    : QGuiApplication (argc, argv, flags)
{
}

Application::~Application()
{
}

void Application::initialize(QQmlApplicationEngine *engine)
{
    createObjects(engine);
    registerTypes();
    createBindings();
    loadResources();
    setContextProperties();
}

void Application::createObjects(QQmlApplicationEngine *engine)
{
    m_engine = engine;

    m_globalManager = new GlobalManager(this);
    m_sprintManager = new SprintManager(this);
    m_storyManager = new StoryManager(this);
    m_taskManager = new TaskManager(this);
    m_userManager = new UserManager(this);
    m_popupManager = new PopupManager(this);
    m_tooltipManager = new TooltipManager(this);
    m_themeManager = new ThemeManager(m_engine, this);
    m_xmlSerializer = new XmlSerializer(this);
}

void Application::registerTypes() const
{
    qRegisterMetaType<Sprint*>("Sprint*");
    qRegisterMetaType<Story*>("Story*");
    qRegisterMetaType<Task*>("Task*");
    qRegisterMetaType<User*>("User*");

    qmlRegisterUncreatableType<Task>("com.cpb", 1, 0, "Task", "Task can't be instantiated directly");
    qmlRegisterUncreatableType<Sprint>("com.cpb", 1, 0, "Sprint", "Sprint can't be instantiated directly");
    qmlRegisterUncreatableType<TaskManager>("com.cpb", 1, 0, "TaskManager", "TaskManager can't be instantiated directly");
    qmlRegisterUncreatableType<PopupManager>("com.cpb", 1, 0, "PopupManager", "PopupManager can't be instantiated directly");
    qmlRegisterUncreatableType<TooltipManager>("com.cpb", 1, 0, "TooltipManager", "TooltipManager can't be instantiated directly");
}

void Application::createBindings() const
{
    connect(m_xmlSerializer, &XmlSerializer::showWelcomeRead, m_globalManager, &GlobalManager::setShowWelcome);
    connect(m_xmlSerializer, &XmlSerializer::modelLoaded, m_globalManager, &GlobalManager::setAppReady);
    connect(m_xmlSerializer, &XmlSerializer::modelLoaded, m_sprintManager, &SprintManager::onModelLoaded);

    connect(m_globalManager, &GlobalManager::showWelcomeChanged, m_xmlSerializer, &XmlSerializer::updateShowWelcome);

    connect(m_sprintManager, &SprintManager::sprintCreated, m_xmlSerializer, &XmlSerializer::createSprint);
    connect(m_sprintManager, &SprintManager::sprintRemoved, m_xmlSerializer, &XmlSerializer::removeSprint);

    connect(m_storyManager, &StoryManager::storyCreated, m_xmlSerializer, &XmlSerializer::createStory);
    connect(m_storyManager, &StoryManager::storyRemoved, m_xmlSerializer, &XmlSerializer::removeStory);
    connect(m_storyManager, &StoryManager::storyRowChanged, m_xmlSerializer, &XmlSerializer::updateStoryRow);

    connect(m_taskManager, &TaskManager::taskCreated, m_xmlSerializer, &XmlSerializer::createTask);
    connect(m_taskManager, &TaskManager::taskRemoved, m_xmlSerializer, &XmlSerializer::removeTask);
    connect(m_taskManager, &TaskManager::taskMoved, m_xmlSerializer, &XmlSerializer::updateTaskPosition);
    connect(m_taskManager, &TaskManager::taskDaysCountChanged, m_xmlSerializer, &XmlSerializer::updateTaskDaysCount);
}

void Application::loadResources() const
{
    m_xmlSerializer->readFile(m_sprintManager->sprintModel());
}

void Application::setContextProperties()
{
    QQmlContext* context = m_engine->rootContext();
    context->setContextProperty("_globalManager", m_globalManager);
    context->setContextProperty("_sprintManager", m_sprintManager);
    context->setContextProperty("_storyManager", m_storyManager);
    context->setContextProperty("_taskManager", m_taskManager);
    context->setContextProperty("_userManager", m_userManager);
    context->setContextProperty("_popupManager", m_popupManager);
    context->setContextProperty("_tooltipManager", m_tooltipManager);
    context->setContextProperty("_themeManager", m_themeManager);
}
