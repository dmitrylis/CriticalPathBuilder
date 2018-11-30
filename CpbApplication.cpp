#include "CpbApplication.h"

#include <QMetaType>
#include <QQmlEngine>
#include <QQmlContext>

using namespace CPB;

Application::Application(int &argc, char **argv, int flags)
    : QGuiApplication (argc, argv, flags)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
}

Application::~Application()
{
}

void Application::registerTypes() const
{
    qRegisterMetaType<Sprint*>("Sprint*");
    qRegisterMetaType<Story*>("Story*");
    qRegisterMetaType<Task*>("Task*");

    qmlRegisterUncreatableType<TaskManager>("com.cpb", 1, 0, "TaskManager", "TaskManager can't be instantiated directly");
}

void Application::createBindings() const
{
    connect(&m_xmlSerializer, &XmlSerializer::modelLoaded, &m_sprintManager, &SprintManager::onModelLoaded);
    connect(&m_sprintManager, &SprintManager::sprintCreated, &m_xmlSerializer, &XmlSerializer::createSprint);
    connect(&m_sprintManager, &SprintManager::sprintRemoved, &m_xmlSerializer, &XmlSerializer::removeSprint);
    connect(&m_storyManager, &StoryManager::storyCreated, &m_xmlSerializer, &XmlSerializer::createStory);
    connect(&m_storyManager, &StoryManager::storyRemoved, &m_xmlSerializer, &XmlSerializer::removeStory);
    connect(&m_storyManager, &StoryManager::storyRowChanged, &m_xmlSerializer, &XmlSerializer::updateStoryRow);
    connect(&m_taskManager, &TaskManager::taskCreated, &m_xmlSerializer, &XmlSerializer::createTask);
    connect(&m_taskManager, &TaskManager::taskMoved, &m_xmlSerializer, &XmlSerializer::moveTask);
    connect(&m_taskManager, &TaskManager::taskRemoved, &m_xmlSerializer, &XmlSerializer::removeTask);
    connect(&m_taskManager, &TaskManager::taskDaysCountChanged, &m_xmlSerializer, &XmlSerializer::updateDaysCount);
}

void Application::loadResources() const
{
    m_xmlSerializer.readFile(m_sprintManager.sprintModel());
}

void Application::setContextProperties(const QQmlApplicationEngine& engine)
{
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("_sprintManager", &m_sprintManager);
    context->setContextProperty("_storyManager", &m_storyManager);
    context->setContextProperty("_taskManager", &m_taskManager);
    context->setContextProperty("_popupManager", &m_popupManager);
}
