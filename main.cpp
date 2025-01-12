#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("babatg");
    app.setOrganizationDomain("babatg.com");
    app.setApplicationName("babnote");

    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");

    QQmlApplicationEngine engine;
    engine.addImportPath(":/babatg");
    engine.load(QString("qrc:/babatg/babnote/main.qml"));
    return app.exec();
}
