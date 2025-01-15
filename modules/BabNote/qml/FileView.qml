import QtQuick 2.15
import QtQuick.Controls
import BabNote.Elements 1.0

Item {
    id: root
    width: 200 // Default width for the FileView
    height: parent.height // Default height for the FileView

    required property INoteController controller

    signal noteSelected(int noteId)

    ListView {
        // File view component
        id: fileList
        width: root.width
        height: root.height
        spacing: 5

        model: ListModel {
            id: modelComponent
            Component.onCompleted: {
                console.log("reloading notes")
                root.reloadNotes()
                // noteId
                // title
            }
        }

        delegate: Item {
            id: noteItem
            width: root.width

            required property string title
            required property int noteId

            height: 50

            Rectangle {
                id: noteRect
                anchors.fill: parent
                anchors.margins: 5

                Text {
                    anchors.fill: parent
                    text: noteItem.title
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                color: "#222222"
                radius: 5

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: mouse => {
                                   if (mouse.button == Qt.LeftButton) {
                                       root.noteSelected(noteItem.noteId)
                                   } else {
                                       contextMenu.open()
                                   }
                               }

                    FileViewMenu {
                        id: contextMenu
                        controller: root.controller
                        noteId: noteItem.noteId
                    }
                }
            }
        }
    }

    Connections {
        target: controller
        function onUpdated() {
            root.reloadNotes()
        }
    }
    function reloadNotes() {
        fileList.model.clear()
        console.log("reloading")
        let notesVec = controller.getNotes()
        for (const noteId of notesVec) {
            let title = controller.getNoteName(noteId)
            fileList.model.append({
                                      "noteId": noteId,
                                      "title": title
                                  })
        }
        console.log("finished")
    }
}
