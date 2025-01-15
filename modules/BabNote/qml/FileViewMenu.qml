import QtQuick
import QtQuick.Controls
import BabNote.Elements 1.0

Item {
    id: root
    required property int noteId
    required property INoteController controller
    function open() {
        contextMenu.open()
    }

    Menu {
        title: "Actions"
        id: contextMenu

        background: Rectangle {
            implicitWidth: 200 // Set here the width you want
            color: "#2f2e2e"
            radius: 10
            border.width: 100
            border.color: "#2f2e2e"
        }

        MenuItem {
            background: Rectangle {
                radius: 10
                color: "#2f2e2e"
            }
            text: "Delete"
            onClicked: {
                root.controller.removeNote(root.noteId)
                stack.pop()
            }
        }
        MenuItem {
            background: Rectangle {
                radius: 10
                color: "#2f2e2e"
            }

            text: "Placeholder"
            onClicked: {

            }
        }
    }
}
