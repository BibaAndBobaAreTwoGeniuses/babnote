#ifndef MARKDOWNNOTE_H
#define MARKDOWNNOTE_H

#include <QObject>
#include "note.h"

class MarkdownNote : public Note
{
    Q_OBJECT

    Q_PROPERTY(QString contents READ contents WRITE setContents NOTIFY contentsChanged FINAL)
    QString m_contents;
public:
    explicit MarkdownNote(QObject *parent = nullptr);


    QString serialize() override;
    void deserialize(const QString &json_contents) override;
    Q_INVOKABLE QString getType() override;

public slots:
    QString contents();
    void setContents(QString new_contents);

signals:
    void contentsChanged();
};

#endif // MARKDOWNNOTE_H
