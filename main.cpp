#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CpbSprintManager.h"
#include "CpbStoryManager.h"
#include "CpbTaskManager.h"
#include "CpbPopupManager.h"
#include "CpbXmlSerializer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // register types
    qRegisterMetaType<CPB::Sprint*>("Sprint*");
    qRegisterMetaType<CPB::Story*>("Story*");
    qRegisterMetaType<CPB::Task*>("Task*");

    // create instances
    CPB::SprintManager sprintManager;
    CPB::StoryManager storyManager;
    CPB::TaskManager taskManager;
    CPB::PopupManager popupManager;
    CPB::XmlSerializer xmlSerializer;

    // connects
    QObject::connect(&xmlSerializer, &CPB::XmlSerializer::modelLoaded, &sprintManager, &CPB::SprintManager::onModelLoaded);
    QObject::connect(&sprintManager, &CPB::SprintManager::sprintCreated, &xmlSerializer, &CPB::XmlSerializer::createSprint);
    QObject::connect(&sprintManager, &CPB::SprintManager::sprintRemoved, &xmlSerializer, &CPB::XmlSerializer::removeSprint);
    QObject::connect(&storyManager, &CPB::StoryManager::storyCreated, &xmlSerializer, &CPB::XmlSerializer::createStory);
    QObject::connect(&storyManager, &CPB::StoryManager::storyRemoved, &xmlSerializer, &CPB::XmlSerializer::removeStory);
    QObject::connect(&storyManager, &CPB::StoryManager::storyRowChanged, &xmlSerializer, &CPB::XmlSerializer::updateStoryRow);
    QObject::connect(&taskManager, &CPB::TaskManager::taskCreated, &xmlSerializer, &CPB::XmlSerializer::createTask);
    QObject::connect(&taskManager, &CPB::TaskManager::taskMoved, &xmlSerializer, &CPB::XmlSerializer::moveTask);
    QObject::connect(&taskManager, &CPB::TaskManager::taskRemoved, &xmlSerializer, &CPB::XmlSerializer::removeTask);

    // load model from xml
    xmlSerializer.readFile(sprintManager.sprintModel());

    // set context properties to qml root context
    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("_sprintManager", &sprintManager);
    rootContext->setContextProperty("_storyManager", &storyManager);
    rootContext->setContextProperty("_taskManager", &taskManager);
    rootContext->setContextProperty("_popupManager", &popupManager);

    engine.load(QUrl(QStringLiteral("qrc:/qml/CpbMain.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
