#include "markdownnote.h"
#include <QDebug>


MarkdownNote::MarkdownNote(QObject *parent)
    : Note{parent}
{
}

QString MarkdownNote::getType()
{
    return "markdown";
}

QString MarkdownNote::contents()
{
    return m_contents;
}

void MarkdownNote::setContents(QString new_contents)
{
    // при автосохранении (или ручном сохранении) вызывается этот метод. Тут еще надо вызвать
    if (new_contents != m_contents) {
        m_contents = new_contents;
        emit contentsChanged();
    }
}

