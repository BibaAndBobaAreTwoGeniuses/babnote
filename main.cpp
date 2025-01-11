#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath(":/babatg");
    engine.load(QString("qrc:/babatg/babnote/main.qml"));
    return app.exec();
}
