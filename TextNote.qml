import QtQuick
import QtQuick.Controls

Note {
    id: root


    TextInput { // MarkdownNote title
        id: noteTitle
        font.pointSize: 20
        font.bold: true
        color: "white"
        text: root.name
        focus: true
        width: parent.width - parent.width * 0.25 - 20

        onTextChanged: {
            root.name = noteTitle.text
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
            root.contents = text
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
            root.saveNote();
        } else if (event.key === Qt.Key_M && event.modifiers & Qt.ControlModifier) {
            switchMode();
        }
    }
}
