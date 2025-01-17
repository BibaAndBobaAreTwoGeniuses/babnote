#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <qqml.h>
#include <qtmetamacros.h>


using NoteId = int;

class NoteModel : public QSqlTableModel
{
    Q_OBJECT
public:
    QML_ELEMENT
    QML_UNCREATABLE("NoteModel is base abstract class for all note controllers")

    virtual ~NoteModel() = default;

    Q_INVOKABLE virtual NoteId createNote() = 0;
    Q_INVOKABLE virtual void removeNote(NoteId id) = 0;

    Q_INVOKABLE virtual QString getNoteName(NoteId id) const = 0;
    Q_INVOKABLE virtual int64_t getNoteCreationTimestamp(NoteId id) const = 0;
    Q_INVOKABLE virtual int64_t getNoteUpdateTimestamp(NoteId id) const = 0;

    Q_INVOKABLE virtual void seNoteName(NoteId id, const QString& name) = 0;
    Q_INVOKABLE virtual QString getNoteText(NoteId id) const = 0;
    Q_INVOKABLE virtual void setNoteText(NoteId id, const QString& text) = 0;
    Q_INVOKABLE virtual Qt::TextFormat getNoteTextFormat(NoteId id) const = 0;
    Q_INVOKABLE virtual void setNoteTextFormat(NoteId id, Qt::TextFormat format) = 0;
    Q_INVOKABLE virtual QString getNoteTags(NoteId id) const = 0;
    Q_INVOKABLE virtual void setNoteTags(NoteId id, const QString& tags) = 0;
    Q_INVOKABLE virtual void updateNote(NoteId id, const QString &name, const QString &contents, const QString &tags) = 0;
signals:
};

#endif // NOTEMODEL_H
