#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <qtmetamacros.h>
#include <QNetworkReply>


class QNetworkAccessManager;
class NetworkController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:
    QNetworkAccessManager* manager;
public:
    explicit NetworkController(QObject *parent = nullptr);
    ~NetworkController();

    Q_INVOKABLE void saveDB();
    Q_INVOKABLE void loadDB();

public slots:
    // void finished(QNetworkReply* reply);
signals:
};

#endif // NETWORKCONTROLLER_H
