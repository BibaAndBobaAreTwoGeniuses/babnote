import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    color: "#111111"
    title: qsTr("Hello World")

    Rectangle { // Background for any note

        width: parent.width * 0.75
        height: parent.height * 0.95
        anchors.left: listview.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        color: "#222222"
        radius: 5
    }

    TextEdit { // MarkdownNote component
        id: textedit
        font.pointSize: 16
        color: "white"
        textFormat: TextEdit.MarkdownText
        text: "**sdadsjad**"
        focus: true
        wrapMode: TextEdit.Wrap
        width: parent.width - parent.width * 0.25 - 20


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
                if (textedit.textFormat == TextEdit.PlainText) {
                    textedit.textFormat = TextEdit.MarkdownText
                } else {
                    textedit.textFormat = TextEdit.PlainText
                }
            }
            text: "Edit\Read modes"
        }
        Button {
            text: "Save .md file"
        }
    }


    ListView { // File view component
        id: listview
        width: parent.width * 0.15
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.bottom: parent.bottom
        spacing: 10

        model: ListModel {
            ListElement {
                text: "note1"

            }
            ListElement {
                text: "note2"

            }
            ListElement {
                text: "fuck"

            }

        }
        delegate: Item {
            width: ListView.view.width
            height: 40
            Rectangle {
                radius: 10
                anchors.fill: parent

                color: "#222222"
                Text {
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.left: parent.left
                   anchors.leftMargin: 10
                   text: model.text
                   color: "white"
                   font.pixelSize: 14
                }
            }
        }
    }



}
