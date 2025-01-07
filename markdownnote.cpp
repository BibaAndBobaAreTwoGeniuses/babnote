#include "markdownnote.h"
#include <QDebug>


MarkdownNote::MarkdownNote(QObject *parent)
    : Note{parent}, m_contents("### contents")
{
    m_title = "title";
}

QString MarkdownNote::serialize()
{
    // тут ничо не надо сериализовывать можно и просто как текст хранить, а в канбане уже надо будет
    return m_contents;
}

void MarkdownNote::deserialize(const QString &json_contents)
{
    // Десериализовывать тоже ничо не надо
    m_contents = json_contents;
}

QString MarkdownNote::getType()
{
    // Мб сделать енам с типами?
    return "markdown";
}

QString MarkdownNote::contents()
{
    return m_contents;
}

void MarkdownNote::saveContents(QString new_contents)
{
    // при автосохранении (или ручном сохранении) вызывается этот метод
    if (new_contents != m_contents) {
        m_contents = new_contents;
        emit contentsChanged();
    }
    qDebug() << "saving called";
    qDebug() << "contents: " << m_contents << "\ntitle:" << m_title;
}

void MarkdownNote::debugContent()
{
    qDebug() << m_contents;
}
