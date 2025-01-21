#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "modules/BabNoteElements/src/NetworkController.h".h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("babatg");
    app.setOrganizationDomain("babatg.com");
    app.setApplicationName("babnote");

    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");

    QQmlApplicationEngine engine;



    engine.addImportPath("qrc:/");

    NetworkController networkController;
    engine.rootContext()->setContextProperty("networkController", &networkController);

    engine.loadFromModule("BabNote", "Main");



    return app.exec();
}
