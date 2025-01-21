#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QQmlEngine>
#include <cstdint>
#include <qtmetamacros.h>
#include <SqlNoteModel.h>
using NoteId = int;



class Note : public QObject
{
public:
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(SqlNoteModel* noteModel MEMBER m_noteModel REQUIRED)
    Q_PROPERTY(NoteId noteId MEMBER m_noteId REQUIRED) // Неизменяемая типа, айди постоянный, хз можно ли сделать ее REQUIRED с READ только

    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged REQUIRED)

    Q_PROPERTY(QString contents MEMBER m_contents NOTIFY contentsChanged FINAL)
    Q_PROPERTY(QString tags MEMBER m_tags NOTIFY tagsChanged FINAL)
    Q_PROPERTY(Qt::TextFormat textFormat MEMBER m_textFormat NOTIFY textFormatChanged FINAL)

    Q_PROPERTY(int64_t noteCreationTimestamp READ getNoteCreationTimestamp FINAL)
    Q_PROPERTY(int64_t noteUpdateTimestamp READ getNoteUpdateTimestamp FINAL)



    SqlNoteModel* m_noteModel{nullptr};
    NoteId m_noteId;
    QString m_name;

    QString m_tags;
    QString m_contents;
    Qt::TextFormat m_textFormat;

    int64_t m_noteCreationTimestamp;
    int64_t m_noteUpdateTimestamp;

public:
    explicit Note(QObject *parent = nullptr);
    ~Note();

    Q_INVOKABLE void saveName();
    Q_INVOKABLE void saveContents();
    Q_INVOKABLE void saveTextFormat();
    Q_INVOKABLE void setTags();
    Q_INVOKABLE void saveNote();
    Q_INVOKABLE void switchMode();


    
public slots:
    int64_t getNoteCreationTimestamp() const;
    int64_t getNoteUpdateTimestamp() const;
signals:
    void nameChanged(const QString& newTitle);
    void contentsChanged(const QString& newContents);
    void tagsChanged(const QString& newTags);
    void textFormatChanged();
};

#endif // NOTE_H
