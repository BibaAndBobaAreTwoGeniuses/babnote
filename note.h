#ifndef NOTE_H
#define NOTE_H

#include <QObject>




class Note : public QObject
{
private:
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    QString m_title;

public:
    explicit Note(QObject *parent = nullptr);

    virtual QString serialize() = 0;
    virtual void deserialize(const QString &json_contents) = 0;
    Q_INVOKABLE virtual QString getType() = 0;

    virtual ~Note() = default;
signals:
    void titleChanged();
public slots:
    QString title();
    void setTitle(QString new_title);
};

#endif // NOTE_H
