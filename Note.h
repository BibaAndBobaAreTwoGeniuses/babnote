#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QQmlEngine>
#include <cstdint>
#include <qtmetamacros.h>
#include "INoteController.h"

class Note : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(INoteController* controller MEMBER m_controller REQUIRED)
    Q_PROPERTY(NoteId noteId MEMBER m_noteId REQUIRED) // Неизменяемая типа, айди постоянный, хз можно ли сделать ее REQUIRED с READ только

    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged REQUIRED)
    Q_PROPERTY(QString type MEMBER m_type REQUIRED) // Неизменяемый тип, типа markdown, richtext, plaintext
    Q_PROPERTY(QString contents MEMBER m_contents NOTIFY contentsChanged FINAL)
    Q_PROPERTY(QString tags MEMBER m_tags NOTIFY tagsChanged FINAL)
    Q_PROPERTY(Qt::TextFormat textFormat MEMBER m_textFormat NOTIFY textFormatChanged FINAL)

    Q_PROPERTY(int64_t noteCreationTimestamp READ getNoteCreationTimestamp FINAL)
    Q_PROPERTY(int64_t noteUpdateTimestamp READ getNoteUpdateTimestamp FINAL)



    INoteController* m_controller;
    NoteId m_noteId;
    QString m_name;
    QString m_type;
    QString m_tags;
    QString m_contents;
    Qt::TextFormat m_textFormat;

    int64_t m_noteCreationTimestamp;
    int64_t m_noteUpdateTimestamp;

public:
    explicit Note(QObject *parent = nullptr);

    Q_INVOKABLE void saveName();
    Q_INVOKABLE void saveContents();
    Q_INVOKABLE void saveTextFormat();
    Q_INVOKABLE void setTags();
    Q_INVOKABLE void saveNote();
    Q_INVOKABLE void switchMode();
    
public slots:
    int64_t getNoteCreationTimestamp() const {
        return m_controller->getNoteCreationTimestamp(m_noteId);
    }
    int64_t getNoteUpdateTimestamp() const {
        return m_controller->getNoteUpdateTimestamp(m_noteId);
    }
signals:
    void nameChanged(const QString& newTitle);
    void contentsChanged(const QString& newContents);
    void tagsChanged(const QString& newTags);
    void textFormatChanged();
};

#endif // NOTE_H
