import QtQuick 2.15
import QtQuick.Controls
Item {
    id: root
    width: 200 // Default width for the FileView
    height: parent.height // Default height for the FileView

    //property INoteController controller: DBNoteController {}

    Component {
        id: markdownNoteComponent
        TextNote {
        }
    }



    ListView { // File view component
        id: fileViewList
        width: root.width
        height: root.height
        spacing: 5

        model: ListModel {
            id: modelComponent
            Component.onCompleted: {
                console.log("reloading notes");
                root.reloadNotes();
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
                    onClicked: (mouse) => {
                        if (mouse.button == Qt.LeftButton) {
                            stack.pop()
                            var obj = markdownNoteComponent.createObject(stack, {noteId: noteItem.noteId, title: noteItem.title, contents: controller.getNoteText(noteId), type: "markdown"})
                            stack.push(obj)
                        } else {
                            contextMenu.open()
                        }
                    }

                    FileViewMenu {
                        id: contextMenu
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
        fileViewList.model.clear()
        console.log("reloading")
        let notesVec = controller.getNotes()
        for (const noteId of notesVec) {
            let title = controller.getNoteName(noteId)
            fileViewList.model.append({noteId: noteId, title: title})
        }
    }







}
