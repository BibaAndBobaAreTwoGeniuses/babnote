import QtQuick


Item {
    id: root


    required property int noteId
    property string contents
    required property string title
    required property string type

    TextInput { // MarkdownNote title
        id: noteTitle
        font.pointSize: 20
        font.bold: true
        color: "white"
        text: root.title
        focus: true
        width: parent.width - parent.width * 0.25 - 20

        onTextChanged: {
            title = text
        }
        onActiveFocusChanged: {

        }
    }

    TextEdit {
        id: noteEditor
        font.pointSize: 14
        color: "white"
        textFormat: TextEdit.MarkdownText
        text: root.contents
        focus: true
        wrapMode: TextEdit.Wrap
        anchors.top: parent.top
        anchors.topMargin: 40
        width: parent.width - parent.width * 0.25 - 20

        onTextChanged: {
            contents = text
        }
    }

    function switchMode() {
        if (type === "markdown") {
            if (noteEditor.textFormat === TextEdit.MarkdownText) {
                noteEditor.textFormat = TextEdit.PlainText
            } else {
                noteEditor.textFormat = TextEdit.MarkdownText
            }
        }
    }


    Keys.onPressed: {
        if (event.key === Qt.Key_S && event.modifiers & Qt.ControlModifier) {
            saveNote();
        } else if (event.key === Qt.Key_M && event.modifiers & Qt.ControlModifier) {
            switchMode();
        }
    }



    function saveNote() {
        let noteId = root.noteId
        let noteContents = root.contents
        let noteName = root.title

        controller.setNoteText(noteId, noteContents)
        controller.setNoteName(noteId, noteName)
    }
}
