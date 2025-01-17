#ifndef SQLNOTEMODEL_H
#define SQLNOTEMODEL_H

#include "NoteModel.h"
#include <qqml.h>
#include <qtmetamacros.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

using NoteId = int;

static QSqlDatabase makeDatabase()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("babatg");
    db.setDatabaseName("babnote.sqlite");
    db.setUserName("babatg");
    db.setPassword("babatg");

    if (!db.open()) {

        throw std::runtime_error("bobo " + db.lastError().text().toStdString());
    }

    auto queryStr = QString("CREATE TABLE IF NOT EXISTS notes("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "name TINYTEXT,"
                            "text LONGTEXT,"
                            "textFormat INTEGER,"
                            "tags LONGTEXT,"
                            "created TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                            "updated TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                            ");");
    QSqlQuery query(db);
    if (!query.prepare(queryStr)) {
        auto msg = query.lastError().text();
        throw std::runtime_error(msg.toStdString());
    }
    if (!query.exec()) {
        auto msg = "Unable to execute query: " + query.lastError().text();
        throw std::runtime_error(msg.toStdString());
    }

    return db;
}


class SqlNoteModel : QSqlTableModel
{
    Q_OBJECT
public:
    QML_ELEMENT
    explicit SqlNoteModel(QObject *parent = nullptr);



    // Overriden necessary functions
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override { return roles; }

    // Has-to-do with notes functions
    Q_INVOKABLE NoteId createNote();
    Q_INVOKABLE void removeNote(NoteId noteId);
    Q_INVOKABLE QString getNoteName(NoteId noteId) const;
    Q_INVOKABLE void setNoteName(NoteId noteId, const QString& name);
    Q_INVOKABLE QString getNoteText(NoteId noteId) const;
    Q_INVOKABLE void setNoteText(NoteId id, const QString& text);
    Q_INVOKABLE Qt::TextFormat getNoteTextFormat(NoteId id) const;
    Q_INVOKABLE void setNoteTextFormat(NoteId id, Qt::TextFormat format);
    Q_INVOKABLE QString getNoteTags(NoteId id) const;
    Q_INVOKABLE void setNoteTags(NoteId id, const QString& tags);
    Q_INVOKABLE void updateNote(NoteId id, const QString &name, const QString &contents, const QString &tags);

    int64_t getNoteCreationTimestamp(NoteId id) const;
    int64_t getNoteUpdateTimestamp(NoteId id) const;
private:
    void generateRoles();

    QVariant getFieldValue(NoteId noteId, const QString &fieldName) const;
    void setFieldValue(NoteId noteId, const QString &fieldName, const QVariant &fieldValue);
    bool nameExists(const QString& title) const;
    
    QHash<int, QByteArray> roles;
    QSqlDatabase db;
signals:
};

#endif // SQLNOTEMODEL_H
