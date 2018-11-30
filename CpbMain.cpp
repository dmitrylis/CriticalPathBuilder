#include "CpbApplication.h"

#include <QQmlEngine>

int main(int argc, char *argv[])
{
    CPB::Application cpbApplication(argc, argv);
    QQmlApplicationEngine engine;

    cpbApplication.registerTypes();
    cpbApplication.createBindings();
    cpbApplication.loadResources();
    cpbApplication.setContextProperties(engine);

    engine.load(QUrl(QStringLiteral("qrc:/qml/CpbMain.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return cpbApplication.exec();
}
