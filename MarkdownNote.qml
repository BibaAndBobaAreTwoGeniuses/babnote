import QtQuick


Item {
    id: mdnote
    property alias textEdit: textedit

    property string uuid
    property string contents
    property string title
    property string type: "markdown"

    TextEdit { // MarkdownNote title
        id: textedittitle
        font.pointSize: 20
        font.bold: true
        color: "white"
        text: mdnote.title
        focus: true
        width: parent.width - parent.width * 0.25 - 20

        onTextChanged: {
            title = text.replace("\n", "") // Чтобы не было слишком затратно изменения отслеживает внутренняя переменная
        }
    }

    TextEdit { // MarkdownNote component
        id: textedit
        font.pointSize: 16
        color: "white"
        textFormat: TextEdit.MarkdownText
        text: mdnote.contents
        focus: true
        wrapMode: TextEdit.Wrap
        anchors.top: parent.top
        anchors.topMargin: 40
        width: parent.width - parent.width * 0.25 - 20

        onTextChanged: {
            contents = text // Чтобы не было слишком затратно изменения отслеживает внутренняя переменная
        }
    }
}
