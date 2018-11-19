#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CpbSprintManager.h"
#include "CpbStoryManager.h"
#include "CpbTaskManager.h"
#include "CpbPopupManager.h"
#include "xmlSerializer.h"
#include "CpbPopupManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // custom section
    CPB::SprintManager sprintManager;
    CPB::StoryManager storyManager;
    CPB::TaskManager taskManager;
    CPB::PopupManager popupManager;

    xmlSerializer xml;

    //connect section
    QObject::connect(&sprintManager, &CPB::SprintManager::sprintCreated, &xml, &xmlSerializer::xmlAddSprint);
    QObject::connect(&storyManager, &CPB::StoryManager::storyCreated, &xml, &xmlSerializer::xmlAddStory);
    QObject::connect(&taskManager, &CPB::TaskManager::taskCreated, &xml, &xmlSerializer::xmlAddTask);

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
