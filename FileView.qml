import QtQuick 2.15

Item {
    id: fileViewRoot
    width: 200 // Default width for the FileView
    height: 400 // Default height for the FileView

    ListView { // File view component
        id: fileViewList
        width: fileViewRoot.width
        height: fileViewRoot.height
        spacing: 10

        model: ListModel {
            ListElement { text: "note1" }
            ListElement { text: "note2" }
            ListElement { text: "fuck" }
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
                    text: model.text // Bind to the model's text property
                    color: "white"
                    font.pixelSize: 14
                }
            }
        }
    }
}
