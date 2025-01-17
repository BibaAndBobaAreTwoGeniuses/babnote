import QtQuick 2.15
import QtQuick.Controls
import BabNote.Elements 1.0



Item {
    id: root
    width: 200 // Default width for the FileView
    height: parent.height // Default height for the FileView

    required property SqlNoteModel noteModel

    signal noteSelected(int noteId)

    ListView {
        // File view component
        id: fileList
        width: root.width
        height: root.height
        spacing: 5

        model: root.noteModel

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
                        noteModel: root.noteModel
                        noteId: id
                    }
                }
            }
        }
    }

    Connections {
        target: root.noteModel
        function onUpdated() {
            //root.reloadNotes()
        }
    }
  
}
