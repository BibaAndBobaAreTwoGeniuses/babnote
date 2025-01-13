import QtQuick
import QtQuick.Controls

Item {
    id: root

    required property INoteController controller
    required property int noteId
    required property string name
    required property string type
    property string contents

    Note {
        id: note
        controller: root.controller
        noteId: root.noteId
        name: root.name
        type: root.type
        contents: root.contents
    }

    TextInput { // MarkdownNote title
        id: noteTitle
        font.pointSize: 20
        font.bold: true
        color: "white"
        text: note.name
        focus: true
        width: parent.width - parent.width * 0.25 - 20

        onTextChanged: {
            note.name = text
        }
    }


    TextEdit {
        id: noteEditor
        font.pointSize: 14
        color: "white"
        textFormat: note.textFormat
        text: note.contents
        focus: true
        wrapMode: TextEdit.Wrap
        anchors.top: parent.top
        anchors.topMargin: 40
        width: parent.width - parent.width * 0.25 - 20

        onTextChanged: {
            note.contents = text
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
