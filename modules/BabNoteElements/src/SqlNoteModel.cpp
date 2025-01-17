#include "SqlNoteModel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <qlogging.h>
#include <qnamespace.h>
#include <quuid.h>


SqlNoteModel::SqlNoteModel(QObject *parent) : QSqlTableModel{parent, makeDatabase()}
{
    // Подключение к бд нужно создать из вне
    setEditStrategy(QSqlTableModel::OnFieldChange);
    setTable("notes");
    generateRoles();
    select();
}

QVariant SqlNoteModel::data(const QModelIndex &index, int role /* = Qt::UserRole */) const
{
    QVariant value;
    if (role < Qt::UserRole) {
        value = QSqlQueryModel::data(index, role);
    } else {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }

    return value;
}

bool SqlNoteModel::setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */)
{
    if (role == Qt::EditRole) {
        return QSqlTableModel::setData(index, value, role);
    } else if (role >= Qt::UserRole) {
        int colIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), colIdx);
        return QSqlTableModel::setData(modelIndex, value, Qt::EditRole);
    }
    return false;
}

void SqlNoteModel::generateRoles()
{
    roles.clear();
    int nCols = this->columnCount();

    for (auto i = 0; i < nCols; ++i) {
        roles[Qt::UserRole + i + 1] = QVariant(headerData(i, Qt::Horizontal).toString()).toByteArray();
    }
}

QVariant SqlNoteModel::getFieldValue(NoteId noteId, const QString &fieldName) const {
    auto startModel = index(0, fieldIndex("id"));
    if (auto modelList = match(startModel, Qt::EditRole, noteId); modelList.size() != 0) {
        auto row = modelList[0].row();
        auto record = this->record(row);
        return record.value(fieldName);
    }
    return QVariant();
}
void SqlNoteModel::setFieldValue(NoteId noteId, const QString &fieldName, const QVariant &fieldValue) {
    auto startModel = index(0, fieldIndex("id"));
    if (auto modelList = match(startModel, Qt::EditRole, noteId); modelList.size() != 0) {
        auto row = modelList[0].row();
        auto record = this->record(row);
        record.setValue(fieldName, fieldValue);

        if (!setRecord(row, record)) {
            qDebug() << "Could not set" << fieldName << "to" << fieldValue;
        }
        select();
    }
}

NoteId SqlNoteModel::createNote() {
    auto record = this->record();
    record.remove(0); // remove id from the record so it isn't fucked
    record.setValue(record.indexOf("text"), "some text");

    if (!insertRecord(-1, record)) {
        qDebug() << "Could not insert a row";
    }
    select();
    auto insertId = this->query().lastInsertId().toInt();

    setNoteName(insertId, "Untitled " + this->record(this->rowCount() - 1).value("id").toString());

    return insertId;
}

void SqlNoteModel::removeNote(NoteId noteId) {
    auto startModel = index(0, fieldIndex("id"));
    auto row = this->match(startModel, Qt::EditRole, noteId)[0].row();
    if (!removeRow(row)) {
        qDebug() << "Could note remove a note. Why the fuck?";
    }
    select();
}
QString SqlNoteModel::getNoteName(NoteId noteId) const {
    auto field = getFieldValue(noteId, "name");
    if (field.isNull()) {
        qDebug() << "Could not get name";
    }

    return field.toString();
}

void SqlNoteModel::setNoteName(NoteId noteId, const QString& name) {
    auto oldName = getNoteName(noteId);

    if ((oldName != name || oldName.isEmpty()) && !nameExists(name))  {
        qDebug() << "not ecists";
        setFieldValue(noteId, "name", name);
    } else {
        qDebug() << "here";
        setFieldValue(noteId, "name", QUuid::createUuid().toString(QUuid::WithoutBraces).chopped(10));
    }
}
bool SqlNoteModel::nameExists(const QString& title) const
{
    auto startModel = index(0, fieldIndex("name"));
    auto modelList = match(startModel, Qt::EditRole, title);
    return modelList.size() > 0;
}

QString SqlNoteModel::getNoteText(NoteId noteId) const {
    auto field = getFieldValue(noteId, "text");
    if (field.isNull()) {
        qDebug() << "Could not get text";
    }
    return field.toString();
}
void SqlNoteModel::setNoteText(NoteId id, const QString& text) {
    setFieldValue(id, "text", text);
}

Qt::TextFormat SqlNoteModel::getNoteTextFormat(NoteId id) const {
    auto value = getFieldValue(id, "textFormat");
    if (value.isNull()) {
        qDebug() << "Could not get tex format";
    }
    return static_cast<Qt::TextFormat>(value.toInt());
}
void SqlNoteModel::setNoteTextFormat(NoteId id, Qt::TextFormat format) {
    setFieldValue(id, "textFormat", static_cast<int>(format));
}

QString SqlNoteModel::getNoteTags(NoteId id) const {
    auto value = getFieldValue(id, "tags");
    if (value.isNull()) {
        qDebug() << "Could not get tags";
    }
    return value.toString();
}
void SqlNoteModel::setNoteTags(NoteId id, const QString& tags) {
    setFieldValue(id, "tags", tags);
}

void SqlNoteModel::updateNote(NoteId id, const QString &name, const QString &contents, const QString &tags) {
    qDebug() << "updatign note model";
    auto startModel = index(0, fieldIndex("id"));
    if (auto modelList = match(startModel, Qt::EditRole, id); modelList.size() != 0) {
        auto row = modelList[0].row();
        auto record = this->record(row);
        record.setValue("name", name);
        record.setValue("text", contents);
        record.setValue("tags", tags);

        if (!setRecord(row, record)) {
            qDebug() << "Could not update note";
        }
        select();
    }
}

int64_t SqlNoteModel::getNoteCreationTimestamp(NoteId id) const {
    auto value = getFieldValue(id, "created");
    if (value.isNull()) {
        qDebug() << "Could not get created";
    }
    return value.toInt();
}
int64_t SqlNoteModel::getNoteUpdateTimestamp(NoteId id) const {
    auto value = getFieldValue(id, "updated");
    if (value.isNull()) {
        qDebug() << "Could not get created";
    }
    return value.toInt();
}
