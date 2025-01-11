#pragma once
#include "types.h"
#include <QObject>
#include <qqml.h>

class INoteController
    : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QVector<NoteId> notes READ getNotes)
    QML_ELEMENT
    QML_UNCREATABLE("INoteController is base abstract class for all note controllers")

    virtual ~INoteController() = default;

    Q_INVOKABLE virtual QVector<NoteId> getNotes() const = 0;

    Q_INVOKABLE virtual NoteId createNote() = 0;
    Q_INVOKABLE virtual void removeNote(NoteId id) = 0;
    Q_INVOKABLE virtual QString getNoteName(NoteId id) const = 0;
    Q_INVOKABLE virtual void setNoteName(NoteId id, const QString& name) = 0;
    Q_INVOKABLE virtual QString getNoteText(NoteId id) const = 0;
    Q_INVOKABLE virtual void setNoteText(NoteId id, const QString& text) = 0;
    Q_INVOKABLE virtual QStringList getNoteTags(NoteId id) const = 0;
    Q_INVOKABLE virtual void setNoteTags(NoteId id, const QStringList& tags) = 0;
    Q_INVOKABLE virtual int64_t getNoteCreationTimestamp(NoteId id) const = 0;
    Q_INVOKABLE virtual int64_t getNoteUpdateTimestamp(NoteId id) const = 0;

signals:
    void updated();
};
