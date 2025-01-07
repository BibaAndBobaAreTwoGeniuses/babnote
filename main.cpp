#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>


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
    //qmlRegisterType<Note>("Klewy", 1, 0, "Note");


    engine.loadFromModule("noteapp", "Main");






    return app.exec();
}
