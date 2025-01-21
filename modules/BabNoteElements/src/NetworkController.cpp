#include "NetworkController.h"
#include <QHttpMultiPart>
#include <QMimeDatabase>
#include <QMimeType>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>



NetworkController::NetworkController(QObject *parent)
    : QObject{parent}, manager(new QNetworkAccessManager(this))
{
    // connect(manager, &QNetworkAccessManager::finished, this, &NetworkController::finished);
}

NetworkController::~NetworkController()
{
    delete manager;
}



void NetworkController::saveDB()
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile("babnote.sqlite");

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(type.name()));
    qDebug() << type.name();
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"user_name\"; filename=\"babnote.sqlite\"")); // TODO replace user_name
    QFile *file = new QFile("babnote.sqlite"); // hardcoding a bit
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart);

    multiPart->append(filePart);

    QUrl url("http://localhost:8080/upload");
    // Set auth headers and yada yada
    QNetworkRequest req(url);

    QNetworkReply* reply = manager->post(req, multiPart);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::finished, this, [reply, multiPart]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "DB was successfuly saved";
        } else {
            qDebug() << "DB was not saved because womp womp" << reply->errorString();
        }

        reply->deleteLater();
    });
}

void NetworkController::loadDB()
{
    QUrl url("http://localhost:8080/download?username=user_name"); // TODO replace user_name
    // Todo also set headers like auth and yada yada
    QNetworkRequest req(url);

    QNetworkReply* reply = manager->get(req);
    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QFile file("babnote.sqlite");
            file.open(QIODevice::WriteOnly | QIODevice::Truncate);
            file.write(reply->readAll());
            file.flush();
            file.close();
        } else {
            qDebug() << "DB wasn't really loaded because womp womp" << reply->errorString();
        }
        reply->deleteLater();
    });
}



