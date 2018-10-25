#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CpbSprintModel.h"
#include "CpbStoryModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // custom section
    CPB::SprintModel sprintModel;
    engine.rootContext()->setContextProperty("_sprintModel", &sprintModel);
    CPB::StoryModel storyModel;
    engine.rootContext()->setContextProperty("_storyModel", &storyModel);

    engine.load(QUrl(QStringLiteral("qrc:/qml/CpbMain.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
