#include "markdownnote.h"

MarkdownNote::MarkdownNote(QObject *parent)
    : Note{parent}, m_contents("##fuck")
{

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

void MarkdownNote::setContents(QString new_contents)
{
    // при автосохранении (или ручном сохранении) вызывается этот метод
    if (new_contents != m_contents) {
        m_contents = new_contents;
        emit contentsChanged();
    }
}
