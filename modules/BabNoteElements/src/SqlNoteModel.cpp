#include "SqlNoteModel.h"
#include <QSqlDatabase>
#include <QSqlQuery>

SqlNoteModel::SqlNoteModel(QObject *parent)
    : QSqlTableModel{parent}
{
    // Подключение к бд нужно создать из вне
    setEditStrategy(QSqlTableModel::OnFieldChange);
    setTable("notes");
    generateRoles();
    select();
}

QVariant SqlNoteModel::data(const QModelIndex &index, int role)
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

void SqlNoteModel::generateRoles()
{
    roles.clear();
    int nCols = this->columnCount();

    for (auto i = 0; i < nCols; ++i) {
        roles[Qt::UserRole + i + 1] = QVariant(headerData(i, Qt::Horizontal).toString()).toByteArray();
    }
}
