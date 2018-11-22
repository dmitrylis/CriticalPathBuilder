#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CpbSprintManager.h"
#include "CpbStoryManager.h"
#include "CpbTaskManager.h"
#include "CpbPopupManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // register section (when we want to use pointer from Q_PROPERTY)
    qRegisterMetaType<CPB::Sprint*>("Sprint*");

    // custom section
    CPB::SprintManager sprintManager;
    CPB::StoryManager storyManager;
    CPB::TaskManager taskManager;
    CPB::PopupManager popupManager;

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
