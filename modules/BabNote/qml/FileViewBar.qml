import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import BabNote.Elements 1.0

Item {
    id: root
    required property INoteController controller

    RowLayout {
        Layout.minimumWidth: 50
        Layout.fillWidth: true
        spacing: 3
        Button {
            id: newNoteBtn
            Layout.fillWidth: true
            palette.buttonText: "white"
            background: Rectangle {
                color: "#222222"
                radius: 3
                border.color: "#222222"
            }

            text: "Create"
            onClicked: {
                root.controller.createNote()
            }
        }
        Button {
            id: placeholderBtn
            Layout.fillWidth: true
            palette.buttonText: "white"
            background: Rectangle {
                color: "#222222"
                radius: 3
                // border.width: 100;
                border.color: "#222222"
            }

            text: "Anal"
            onClicked: {
                console.log("Anal v2")
            }
        }
    }
}
