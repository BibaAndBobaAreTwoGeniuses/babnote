import QtQuick 2.15
import QtQuick.Controls
Item {
    id: fileViewRoot
    width: 200 // Default width for the FileView
    height: 400 // Default height for the FileView

    property list<string> titles

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

        model: ListModel {
            Component.onCompleted: {
                var notesMap = noteManager.getNotes();
                for (var obj in notesMap) {
                    fileViewList.model.append({uuid: obj, title: notesMap[obj][0]})
                }
            }
        }

        delegate: Item {
            width: fileViewList.width
            height: 50 // Adjust height for buttons

            Button {
                id: control
                anchors.fill: parent // Make the button fill the parent container
                anchors.margins: 5 // Optional margin around the button

                text: title // Display the title property of each item

                contentItem: Text {
                    text: control.text
                    font: control.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: "#222222"
                    radius: 5
                }

                onClicked: {
                    stack.pop();
                    var obj = markdownNoteComponent.createObject(stack, {uuid: uuid, title: title, contents: noteManager.contentsOf(uuid)})
                    stack.push(obj);
                }
            }
        }
    }

    function reloadNotes() {
        fileViewList.model.clear();

        var notesMap = noteManager.getNotes();
        for (var obj in notesMap) {
            fileViewList.model.append({uuid: obj, title: notesMap[obj][0]})
        }
    }
}
