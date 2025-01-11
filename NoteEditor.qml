import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import babnote

Item {
    id: root
    property INoteController noteController
    property int currentNoteId: -1

    onCurrentNoteIdChanged: {
        noteText.text = currentNoteId != -1 ? root.noteController.getNoteText(currentNoteId) : ""
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Button {
                text: "Save"
                onClicked: {
                    root.noteController.setNoteText(root.currentNoteId, noteText.text)
                }
            }
        }

        TextEdit {
            id: noteText
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
