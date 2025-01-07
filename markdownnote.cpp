#include "markdownnote.h"

MarkdownNote::MarkdownNote(QObject *parent)
    : Note{parent}, m_contents("##fuck")
{

}

QString MarkdownNote::serialize()
{
    return m_contents;
}

void MarkdownNote::deserialize(const QString &json_contents)
{
    // Some insense deserialization process...
    m_contents = json_contents;
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
    if (new_contents != m_contents) {
        m_contents = new_contents;
        emit contentsChanged();
    }
}
