#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CpbSprintManager.h"
#include "CpbStoryManager.h"
#include "CpbTaskManager.h"
#include "xmlSerializer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    /*xmlSerializer xml;
    xml.xmlAddSprint("SHIET");*/

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // custom section
    CPB::SprintManager sprintManager;
    CPB::StoryManager storyManager;
    CPB::TaskManager taskManager;

    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("_sprintManager", &sprintManager);
    rootContext->setContextProperty("_storyManager", &storyManager);
    rootContext->setContextProperty("_taskManager", &taskManager);

    engine.load(QUrl(QStringLiteral("qrc:/qml/CpbMain.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
