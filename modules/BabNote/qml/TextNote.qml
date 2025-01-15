import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import BabNote.Elements 1.0

Item {
    id: root

    property INoteController controller
    property int noteId
    property string name
    property string type
    property string contents

    ColumnLayout {
        anchors.fill: parent

        Note {
            id: note
            controller: root.controller
            noteId: root.noteId
            name: root.name
            contents: root.contents
        }

        TextInput {
            id: noteTitle
            Layout.fillWidth: true
            Layout.fillHeight: false
            font.pointSize: 20
            font.bold: true
            color: "white"
            text: note.name
            focus: true

            onTextChanged: {
                note.name = text
            }
        }

        TextEdit {
            id: noteEditor
            Layout.fillWidth: true
            Layout.fillHeight: true
            font.pointSize: 14
            color: "white"
            textFormat: note.textFormat
            text: note.contents
            focus: true
            wrapMode: TextEdit.Wrap

            onTextChanged: {
                note.contents = text
            }
        }
    }

    Shortcut {
        sequence: "Ctrl+S"
        onActivated: {
            note.saveNote()
        }
    }
    Shortcut {
        sequence: "Ctrl+M"
        onActivated: {
            note.switchMode()
        }
    }
}
