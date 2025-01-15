#ifndef SQLNOTEMODEL_H
#define SQLNOTEMODEL_H

#include <QSqlTableModel>

class QSqlDatabase;

class SqlNoteModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit SqlNoteModel(QObject *parent = nullptr);

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole);
    QHash<int, QByteArray> getRoles() const { return roles; }

private:
    QHash<int, QByteArray> roles;
    QSqlDatabase db;
private:
    void generateRoles();
signals:
};

#endif // SQLNOTEMODEL_H
