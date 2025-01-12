import QtQuick
import QtQuick.Controls

Item {
    id: root
    required property int noteId

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
            border.width: 100;
            border.color: "#2f2e2e"
        }

        MenuItem {
            background: Rectangle {
                radius: 10
                color: "#2f2e2e"
            }
            text: "Delete"
            onClicked: {
                controller.removeNote(root.noteId)
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
