#include "notemanager.h"

NoteManager::NoteManager(QObject *parent)
    : QObject{parent}
{
    //NoteDB interaction
    list.append(new ManagerItem{"important", "markdown"});
    list.append(new ManagerItem{"study", "markdown"});
    list.append(new ManagerItem{"study2", "markdown"});

}
NoteManager::~NoteManager() {
    for (int i = 0; i < list.size(); ++i) {
        delete list[i];
    }
}


void NoteManager::saveNote(const QString &title, const QString& type, const QString &contents) {
    // NoteDB interaction
}
