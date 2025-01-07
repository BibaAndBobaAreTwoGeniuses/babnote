#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include "markdownnote.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    //Note note;
    //engine.rootContext()->setContextProperty("obj", &note);
    qmlRegisterType<MarkdownNote>("Klewy", 1, 0, "MdModel");


    engine.loadFromModule("noteapp", "Main");






    return app.exec();
}
