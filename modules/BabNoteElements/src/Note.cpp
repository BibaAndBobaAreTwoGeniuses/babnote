#include "Note.h"
#include "SqlNoteModel.h"



Note::Note(QObject *parent)
    : QObject{parent}
{
}

Note::~Note()
{
}

void Note::saveName() {
    m_noteModel->setNoteName(m_noteId, m_name);
}

void Note::saveContents() {
    m_noteModel->setNoteText(m_noteId, m_contents);
}

void Note::saveTextFormat() {
    m_noteModel->setNoteTextFormat(m_noteId, m_textFormat);
}

void Note::setTags() {
    m_noteModel->setNoteTags(m_noteId, m_tags);
}

void Note::saveNote() {
    qDebug() << "saving a note";
    m_noteModel->updateNote(m_noteId, m_name, m_contents, m_tags);
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
    return m_noteModel->getNoteCreationTimestamp(m_noteId);
}

int64_t Note::getNoteUpdateTimestamp() const {
    return m_noteModel->getNoteUpdateTimestamp(m_noteId);
}
