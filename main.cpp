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

    // register section (when we want to use pointer from Q_PROPERTY)
    qRegisterMetaType<CPB::Sprint*>("Sprint*");
    qRegisterMetaType<CPB::Story*>("Story*");
    qRegisterMetaType<CPB::Task*>("Task*");

    // custom section
    CPB::SprintManager sprintManager;
    CPB::StoryManager storyManager;
    CPB::TaskManager taskManager;
    CPB::PopupManager popupManager;

    CPB::XmlSerializer xml;
    xml.xmlReadFile(sprintManager.sprintModel());

    //connect section
    QObject::connect(&sprintManager, &CPB::SprintManager::sprintCreated, &xml, &CPB::XmlSerializer::xmlAddSprint);
    QObject::connect(&storyManager, &CPB::StoryManager::storyCreated, &xml, &CPB::XmlSerializer::xmlAddStory);
    QObject::connect(&storyManager, &CPB::StoryManager::storyRowChanged, &xml, &CPB::XmlSerializer::xmlChangeStoryRow);
    QObject::connect(&taskManager, &CPB::TaskManager::taskCreated, &xml, &CPB::XmlSerializer::xmlAddTask);

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
