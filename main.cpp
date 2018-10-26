#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "managers/CpbSprintManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // custom section
    CPB::SprintManager sprintManager;
    engine.rootContext()->setContextProperty("_sprintManager", &sprintManager);

    engine.load(QUrl(QStringLiteral("qrc:/qml/CpbMain.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
