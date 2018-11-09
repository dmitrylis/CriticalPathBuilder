#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "managers/CpbSprintManager.h"
#include "managers/CpbStoryManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // custom section
    CPB::SprintManager sprintManager;
    CPB::StoryManager storyManager;

    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("_sprintManager", &sprintManager);
    rootContext->setContextProperty("_storyManager", &storyManager);

    engine.load(QUrl(QStringLiteral("qrc:/qml/CpbMain.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
