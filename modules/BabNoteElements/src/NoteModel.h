#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QObject>

class NoteModel : public QObject
{
    Q_OBJECT
public:
    explicit NoteModel(QObject *parent = nullptr);

signals:
};

#endif // NOTEMODEL_H
