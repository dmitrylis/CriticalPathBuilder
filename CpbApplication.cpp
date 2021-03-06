#include "CpbApplication.h"

#include <QMetaType>
#include <QQmlEngine>
#include <QQmlContext>

using namespace CPB;

Application::Application(int &argc, char **argv, int flags)
    : QGuiApplication (argc, argv, flags)
{
}

Application::~Application()
{
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
    connect(&m_xmlSerializer, &XmlSerializer::showWelcomeRead, &m_globalManager, &GlobalManager::setShowWelcome);
    connect(&m_xmlSerializer, &XmlSerializer::modelLoaded, &m_globalManager, &GlobalManager::setAppReady);
    connect(&m_xmlSerializer, &XmlSerializer::modelLoaded, &m_sprintManager, &SprintManager::onModelLoaded);

    connect(&m_globalManager, &GlobalManager::showWelcomeChanged, &m_xmlSerializer, &XmlSerializer::updateShowWelcome);

    connect(&m_sprintManager, &SprintManager::sprintCreated, &m_xmlSerializer, &XmlSerializer::createSprint);
    connect(&m_sprintManager, &SprintManager::sprintRemoved, &m_xmlSerializer, &XmlSerializer::removeSprint);

    connect(&m_storyManager, &StoryManager::storyCreated, &m_xmlSerializer, &XmlSerializer::createStory);
    connect(&m_storyManager, &StoryManager::storyRemoved, &m_xmlSerializer, &XmlSerializer::removeStory);
    connect(&m_storyManager, &StoryManager::storyRowChanged, &m_xmlSerializer, &XmlSerializer::updateStoryRow);

    connect(&m_taskManager, &TaskManager::taskCreated, &m_xmlSerializer, &XmlSerializer::createTask);
    connect(&m_taskManager, &TaskManager::taskRemoved, &m_xmlSerializer, &XmlSerializer::removeTask);
    connect(&m_taskManager, &TaskManager::taskMoved, &m_xmlSerializer, &XmlSerializer::updateTaskPosition);
    connect(&m_taskManager, &TaskManager::taskDaysCountChanged, &m_xmlSerializer, &XmlSerializer::updateTaskDaysCount);
}

void Application::loadResources() const
{
    m_xmlSerializer.readFile(m_sprintManager.sprintModel());
}

void Application::setContextProperties(const QQmlApplicationEngine& engine)
{
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("_globalManager", &m_globalManager);
    context->setContextProperty("_sprintManager", &m_sprintManager);
    context->setContextProperty("_storyManager", &m_storyManager);
    context->setContextProperty("_taskManager", &m_taskManager);
    context->setContextProperty("_userManager", &m_userManager);
    context->setContextProperty("_popupManager", &m_popupManager);
    context->setContextProperty("_tooltipManager", &m_tooltipManager);
}
