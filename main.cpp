#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "gol.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<GOL>("GOL", 1, 0, "GOL");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
