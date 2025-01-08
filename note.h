#ifndef NOTE_H
#define NOTE_H

#include <QObject>




class Note : public QObject
{
private:
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
protected:
    QString m_title;

public:
    explicit Note(QObject *parent = nullptr);

    virtual void serialize() {}
    virtual void deserialize() {}

    Q_INVOKABLE virtual QString getType() = 0;

    virtual ~Note() = default;

signals:
    void titleChanged();
public slots:
    QString title();
    void setTitle(QString new_title);
};

#endif // NOTE_H
