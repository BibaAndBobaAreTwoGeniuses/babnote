import QtQuick
import Klewy

Item {
    id: mdnote
    property alias textEdit: textedit
    property alias mdModel: mdmodel

    property string contents
    property string title


    MdModel {
        id: mdmodel
        title: mdnote.title
        contents: mdnote.contents
    }

    TextEdit { // MarkdownNote title
        id: textedittitle
        font.pointSize: 20
        font.bold: true
        color: "white"
        text: mdmodel.title
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
        text: mdmodel.contents
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
