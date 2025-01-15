#include "DBNoteController.h"
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>
#include <qsqlquery.h>
#include <qvariant.h>
#include<QUuid>

DBNoteController::DBNoteController()
    : _db()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setHostName("babatg");
    _db.setDatabaseName("babnote.sqlite");
    _db.setUserName("babatg");
    _db.setPassword("babatg");
    _db.open();
    auto queryStr = QString("CREATE TABLE IF NOT EXISTS notes("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TINYTEXT,"
                    "text LONGTEXT,"
                    "textFormat INTEGER,"
                    "tags LONGTEXT,"
                    "created TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                    "updated TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                    ");");
    QSqlQuery query(_db);
    prepareQuery(query, queryStr);
    execQuery(query);

    bool hasFeatures = _db.driver()->hasFeature(QSqlDriver::EventNotifications);
    if (!hasFeatures) {
        auto msg = "Database does not support event notifications";
        throw std::runtime_error(msg);
    }
    
    auto rb = _db.driver()->subscribeToNotification("notes");
    if (!rb) {
        auto msg = "Can not subscribe to db notification: " + _db.lastError().text().toStdString();
        throw std::runtime_error(msg);
    }
    QObject::connect(_db.driver(), &QSqlDriver::notification, this, &DBNoteController::onDbNotification);
}

QVector<NoteId> DBNoteController::getNotes() const
{
    auto queryStr = "SELECT id FROM notes;";
    QSqlQuery q(_db);
    prepareQuery(q, queryStr);
    execQuery(q);
    QVector<NoteId> notes;
    while (q.next()) {
        notes.emplace_back(q.value(0).toLongLong());
    }

    return notes;
}

NoteId DBNoteController::createNote()
{
    auto queryStr = QString("INSERT INTO notes(updated, text) VALUES(CURRENT_TIMESTAMP, \"some text\");");
    QSqlQuery q(_db);
    prepareQuery(q, queryStr);
    execQuery(q);

// FIX: если название заметки заранее сделать Untitled + id будущей заметки то она не создастся
    auto lastInsertId = q.lastInsertId().toLongLong();
    setNoteName(lastInsertId, "Untitled " + QString::number(lastInsertId));
    return lastInsertId;
}

void DBNoteController::removeNote(NoteId id)
{
    auto queryStr = QString("DELETE FROM notes WHERE id=%1;").arg(id);
    QSqlQuery q(_db);
    prepareQuery(q, queryStr);
    execQuery(q);
}

QString DBNoteController::getNoteName(NoteId id) const
{
    return queryField(id, "name").toString();
}

void DBNoteController::setNoteName(NoteId id, const QString& name)
{
    auto oldName = getNoteName(id);
    qDebug() << "here";
    if ((oldName != name || oldName.isEmpty()) && !nameExists(name))  {
        queryField(id, "name", name);
    } else {
        queryField(id, "name", QUuid::createUuid().toString(QUuid::WithoutBraces).chopped(10));
    }
}

QString DBNoteController::getNoteText(NoteId id) const
{
    return queryField(id, "text").toString();
}

void DBNoteController::setNoteText(NoteId id, const QString& text)
{
    queryField(id, "text", text);
}

Qt::TextFormat DBNoteController::getNoteTextFormat(NoteId id) const
{
    return static_cast<Qt::TextFormat>(queryField(id, "textFormat").toInt());
}

void DBNoteController::setNoteTextFormat(NoteId id, Qt::TextFormat format)
{
    queryField(id, "textFormat", static_cast<int>(format));
}

QString DBNoteController::getNoteTags(NoteId id) const
{
    return queryField(id, "tags").toString();
}

void DBNoteController::setNoteTags(NoteId id, const QString &tags)
{
    queryField(id, "tags", tags);
}

int64_t DBNoteController::getNoteCreationTimestamp(NoteId id) const
{
    return queryField(id, "created").toDateTime().toMSecsSinceEpoch();
}

int64_t DBNoteController::getNoteUpdateTimestamp(NoteId id) const
{
    return queryField(id, "updated").toDateTime().toMSecsSinceEpoch();
}



void DBNoteController::prepareQuery(QSqlQuery& query, const QString& s)
{
    if (!query.prepare(s)) {
        auto msg = query.lastError().text().toStdString();
        throw std::runtime_error(msg);
    }
}

void DBNoteController::execQuery(QSqlQuery& query)
{
    if (!query.exec()) {
        auto msg = "Unable to execute query: " + query.lastError().text();
        throw std::runtime_error(msg.toStdString());
    }
}

bool DBNoteController::nameExists(const QString& title) const
{
    auto queryStr = QString("SELECT name FROM notes WHERE name='%1';").arg(title);
    QSqlQuery q(_db);
    prepareQuery(q, queryStr);
    execQuery(q);

    return q.last();
}

QVariant DBNoteController::queryField(NoteId id, const QString& name) const
{
    auto queryStr = QString("SELECT %1 FROM notes WHERE id=%2;").arg(name).arg(id);
    QSqlQuery q(_db);
    prepareQuery(q, queryStr);
    execQuery(q);
    q.next();
    return q.value(0);
}

void DBNoteController::queryField(NoteId id, const QString& name, const QVariant& value)
{
    auto queryStr = QString("UPDATE notes SET %1=\"%2\", updated=CURRENT_TIMESTAMP WHERE id=%3;")
    .arg(name).arg(value.toString()).arg(id);
    QSqlQuery q(_db);
    prepareQuery(q, queryStr);
    execQuery(q);
}

void DBNoteController::onDbNotification(const QString& name)
{
    if (name == "notes") {
        emit updated();
    }
}

void DBNoteController::updateNote(NoteId id, const QString &name, const QString &contents, const QString &tags) {
    QSqlQuery query(_db);
    QString queryStr;

    if (!nameExists(name)) { 
        queryStr = QString("UPDATE notes SET name='%1', text='%2', tags='%3' WHERE id=%4")
        .arg(name)
        .arg(contents)
        .arg(tags)
        .arg(id);
    } else { // Если новое имя уже сущестует в таблице то просто продолжаем не изменяя имя, можно мб сигнал какой то подавать чтоб в ГУИ это отобразить
        queryStr = QString("UPDATE notes SET text='%1', tags='%3' WHERE id=%4")
        .arg(contents)
        .arg(tags)
        .arg(id);
    }

    prepareQuery(query, queryStr);
    execQuery(query);
}
