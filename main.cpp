#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "modules/BabNoteElements/src/SqlNoteModel.h"
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("babatg");
    app.setOrganizationDomain("babatg.com");
    app.setApplicationName("babnote");

    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");

    SqlNoteModel model;


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("modelNote", &model);
    engine.addImportPath("qrc:/");
    engine.loadFromModule("BabNote", "Main");



    return app.exec();
}
