#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>
#include <QList>
#include <QDebug>
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

    Q_INVOKABLE QList<ManagerItem*> getList() {
        return list;
    }

    Q_INVOKABLE QString contentsOf(QString title, QString type) { // Этот метод будет фетчить контент из базы данных
        qDebug() << "func called" << title << type;
        return "## sieg heil";
    }

    void saveNote(const QString &title, const QString& type, const QString &contents);

    QList<ManagerItem*> list;
signals:
};

#endif // NOTEMANAGER_H
