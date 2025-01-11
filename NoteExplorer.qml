import QtQuick
import QtQuick.Controls
import babnote

Item {
    id: root
    property INoteController noteController
    property int noteId: -1

    Menu {
        id: contextMenu
        property int noteId
        modal: true

        MenuItem {
            text: "Delete"
            onClicked: root.noteController.removeNote(contextMenu.noteId)
        }

    }

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

        delegate: Component {
            Item {
                id: notesListViewComp
                required property int index
                required property int noteId
                required property string noteName
                width: parent ? parent.width : 0
                height: 25

                Rectangle {
                    anchors.fill: parent
                    color: notesList.currentIndex == notesListViewComp.index || mouseArea.containsMouse ? "blue" : "transparent"

                    Text {
                        anchors.fill: parent
                        text: notesListViewComp.noteName
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onClicked: (mouse) => {
                            if (mouse.button == Qt.LeftButton) {
                                if (notesList.currentIndex != notesListViewComp.index) {
                                    notesList.currentIndex = notesListViewComp.index
                                    root.noteId = notesListViewComp.noteId
                                } else {
                                    notesList.currentIndex = -1
                                    root.noteId = -1
                                }
                            } else if (mouse.button == Qt.RightButton) {
                                contextMenu.noteId = notesListViewComp.noteId
                                contextMenu.popup()
                            }
                        }
                    }
                }
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
