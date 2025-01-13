#include "note.h"

Note::Note(QObject *parent)
    : QObject{parent}
{
}

void Note::saveName() {
    m_controller->setNoteName(m_noteId, m_name);
}

void Note::saveContents() {
    m_controller->setNoteText(m_noteId, m_contents);
}

void Note::saveTextFormat() {
    m_controller->setNoteTextFormat(m_noteId, m_textFormat);
}

void Note::setTags() {
    m_controller->setNoteTags(m_noteId, m_tags);
}

void Note::saveNote() {
    m_controller->setNoteName(m_noteId, m_name);
    m_controller->setNoteText(m_noteId, m_contents);
    m_controller->setNoteTags(m_noteId, m_tags);
}

void Note::switchMode() {
    if (m_type == "markdown") {
        if (m_textFormat == Qt::MarkdownText) {
            m_textFormat = Qt::PlainText;
        } else {
            m_textFormat = Qt::MarkdownText;
        }
    }
    emit textFormatChanged();
}
