#ifndef SQLNOTEMODEL_H
#define SQLNOTEMODEL_H

#include <QSqlTableModel>
#include <qqml.h>
#include <qtmetamacros.h>

class QSqlDatabase;

class SqlNoteModel : public QSqlTableModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit SqlNoteModel(QObject *parent = nullptr);

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole);
    QHash<int, QByteArray> roleNames() const override { return roles; }

private:
    QHash<int, QByteArray> roles;
    QSqlDatabase db;
private:
    void generateRoles();
signals:
};

#endif // SQLNOTEMODEL_H
