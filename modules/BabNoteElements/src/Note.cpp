#include "Note.h"
#include "INoteController.h"

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
    m_controller->updateNote(m_noteId, m_name, m_contents, m_tags);
}

void Note::switchMode() {
    if (m_textFormat == Qt::MarkdownText) {
        m_textFormat = Qt::PlainText;
    } else {
        m_textFormat = Qt::MarkdownText;
    }
    emit textFormatChanged();
}

int64_t Note::getNoteCreationTimestamp() const {
    return m_controller->getNoteCreationTimestamp(m_noteId);
}

int64_t Note::getNoteUpdateTimestamp() const {
    return m_controller->getNoteUpdateTimestamp(m_noteId);
}
