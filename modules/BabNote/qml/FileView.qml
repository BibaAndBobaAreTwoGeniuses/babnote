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

        model: SqlNoteModel {}

        delegate: Item {
            id: noteItem
            width: root.width

            height: 50

            Rectangle {
                id: noteRect
                anchors.fill: parent
                anchors.margins: 5

                Text {
                    anchors.fill: parent
                    text: name
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
                                       root.noteSelected(id)
                                   } else {
                                       contextMenu.open()
                                   }
                               }

                    FileViewMenu {
                        id: contextMenu
                        controller: root.controller
                        noteId: id
                    }
                }
            }
        }
    }

    Connections {
        target: controller
        function onUpdated() {
            //root.reloadNotes()
        }
    }
    // function reloadNotes() {
    //     fileList.model.clear()
    //     console.log("reloading")
    //     let notesVec = controller.getNotes()
    //     for (const noteId of notesVec) {
    //         let title = controller.getNoteName(noteId)
    //         fileList.model.append({
    //                                   "noteId": noteId,
    //                                   "title": title
    //                               })
    //     }
    //     console.log("finished")
    // }
}
