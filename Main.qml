import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    color: "#111111"
    title: qsTr("Hello World")


    FileView {
        id: listview
        width: parent.width * 0.15
        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.bottom: parent.bottom
    }



    Rectangle { // Background for any note

        width: parent.width * 0.75
        height: parent.height * 0.95
        anchors.left: listview.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        color: "#222222"
        radius: 5
    }

    MarkdownNote {
        id: mdnote
        anchors.left: listview.right
        anchors.leftMargin: parent.width * 0.05
        anchors.top: parent.top
        anchors.topMargin: 50
    }



    Column { // Debug buttons kinda
        anchors.top: parent.top
        anchors.right: parent.right
        spacing: 10
        Button {
            onClicked: {
                if (mdnote.textEdit.textFormat == TextEdit.PlainText) {
                    mdnote.textEdit.textFormat = TextEdit.MarkdownText
                } else {
                    mdnote.textEdit.textFormat = TextEdit.PlainText
                }
            }
            text: "Edit\Read modes"
        }
        Button {
            text: "Save .md file"
            onClicked: { // Это имитация автосейва/ручного сейва, тут уже QML обращается к С++ модели и сохраняет заметку
                mdnote.mdModel.setTitle(mdnote.title); // Правда сначала надо сохранить название обязательно
                mdnote.mdModel.saveContents(mdnote.contents);
            }
        }
    }

}
