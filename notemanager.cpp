#include "notemanager.h"
#include <QVariant>
#include<QVariantList>
NoteManager::NoteManager(QObject *parent)
    : QObject{parent}
{
    //NoteDB interaction
    // list.append(new ManagerItem{"important", "markdown"});
    // noteMap["important"] = "markdown";
}
NoteManager::~NoteManager() {

}


void NoteManager::createNote(const QString &uuid, const QString &title, const QString &type) {
    qDebug() << type << " typepeeeeeed";
    if (!noteMap.contains(title))
        noteMap[uuid] = QVariantList{title, type};
}

void NoteManager::saveNote(const QString &uuid, const QString&title, const QString &contents)
{
    auto list = noteMap[uuid].toList();
    list[0] = title;
    noteMap[uuid].setValue(list);
    content[uuid] = contents;
}
