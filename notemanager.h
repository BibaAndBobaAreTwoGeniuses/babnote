#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H
#include <QUuid>
#include <QObject>
#include <QList>
#include <QDebug>
#include <qmap.h>
#include <QVariantMap>
class ManagerItem : public QObject {
    Q_OBJECT
    QString m_title;
    QString m_type;

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString type READ type CONSTANT)
public:

    ManagerItem(QObject *parent = nullptr)
        : QObject{parent} {

    }
    ManagerItem(QString title, QString type) : m_title(title), m_type(type) {

    }


public slots:
    QString title() {
        return m_title;
    }
    QString type() {
        return m_type;
    }
    void setTitle(QString new_title) {
        m_title = std::move(new_title);
        emit titleChanged();
    }
signals:
    void titleChanged();
};

class NoteManager : public QObject
{
    Q_OBJECT
public:
    explicit NoteManager(QObject *parent = nullptr);
    ~NoteManager();


    static NoteManager& instance() {
        static NoteManager manager;
        return manager;
    }

    Q_INVOKABLE QString getUuid() {
        auto id = QUuid().createUuid().toString();
        qDebug() << id;
        return id;
    }
    
    Q_INVOKABLE QString contentsOf(QString uuid) { // Этот метод будет фетчить контент из базы данных
        qDebug() << "func called" << uuid;
        return content[uuid];
    }

    Q_INVOKABLE bool titleExists(const QString &title) {
        for (auto &item : noteMap) {
            if (item.toList()[0] == title) {
                qDebug() << "exsits";
                return true;
            }
        }
        return false;
    }

    Q_INVOKABLE void createNote(const QString &uuid, const QString &title, const QString &type);
    Q_INVOKABLE void saveNote(const QString &uuid, const QString&title, const QString &contents);

    QMap<QString, QString> content;
    QVariantMap noteMap;
public slots:
    QVariantMap getNotes() {
        return noteMap;
    }
signals:
};

#endif // NOTEMANAGER_H
