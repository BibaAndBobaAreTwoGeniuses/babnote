import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material 2.12
import babnote

Item {
    id: root
    property INoteController noteController
    property int noteId: -1

    ListView {
        id: notesList
        anchors.fill: parent
        currentIndex: -1

        clip: true
        focus: true
        Component.onCompleted: notesList.reloadView()

        model: ListModel {
            id: notesListModel
        }

        delegate: ItemDelegate {
            id: notesListViewComp
            required property int index
            required property int noteId
            required property string noteName
            width: parent ? parent.width : 0
            height: 25
            highlighted: root.noteId == noteId
            onClicked: {
                if (root.noteId != noteId) {
                    root.noteId = noteId
                } else {
                    root.noteId = -1
                }
            }

            Text {
                anchors.fill: parent
                text: notesListViewComp.noteName
                color: Material.foreground
            }
        }

        Connections {
            target: root.noteController
            function onUpdated() {
                notesList.reloadView()
            }
        }

        function reloadView() {
            notesListModel.clear()
            const notes = root.noteController.getNotes()
            for (const noteId of notes) {
                const el = {
                    "noteId": noteId,
                    "noteName": controller.getNoteName(noteId)
                }
                notesListModel.append(el)
            }
        }
    }
}
