#include "note.h"
#include <QDebug>

Note::Note(QObject *parent)
    : QObject{parent}
{}

QString Note::title()
{
    return m_title;
}

void Note::setTitle(QString new_title)
{
    if (new_title != m_title) {
        m_title = new_title;
        emit titleChanged();
    }
}

