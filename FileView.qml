import QtQuick 2.15
import QtQuick.Controls
Item {
    id: fileViewRoot
    width: 200 // Default width for the FileView
    height: 400 // Default height for the FileView


    Component {
        id: markdownNoteComponent
        MarkdownNote {
        }
    }

    ListView { // File view component
        id: fileViewList
        width: fileViewRoot.width
        height: fileViewRoot.height
        spacing: 5

        model: noteManager.getList() // Bind to the model

        delegate: Item {
            width: fileViewList.width
            height: 50 // Adjust height for buttons

            Button {
                id: control
                anchors.fill: parent // Make the button fill the parent container
                anchors.margins: 5 // Optional margin around the button

                text: modelData.title // Display the title property of each item

                contentItem: Text {
                    text: control.text
                    font: control.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    color: "#222222"
                    radius: 5
                }

                onClicked: {
                    console.log("Button clicked:", modelData.title);
                    stack.pop();
                    var obj = markdownNoteComponent.createObject(stack, {title: modelData.title, contents: noteManager.contentsOf(modelData.title, modelData.type)})

                    stack.push(obj);
                }
            }
        }
    }
}
