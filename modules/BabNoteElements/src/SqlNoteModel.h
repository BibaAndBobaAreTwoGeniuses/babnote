#ifndef SQLNOTEMODEL_H
#define SQLNOTEMODEL_H

#include <QSqlTableModel>
#include <qqml.h>
#include <qtmetamacros.h>
#include <QSqlQuery>
#include <QSqlError>
class QSqlDatabase;


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

class SqlNoteModel : public QSqlTableModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit SqlNoteModel(QObject *parent = nullptr);

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override { return roles; }
private:
    void generateRoles();

    QHash<int, QByteArray> roles;
    QSqlDatabase db;
signals:
};

#endif // SQLNOTEMODEL_H
