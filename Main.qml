import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    color: "#111111"
    title: qsTr("Hello World")

    Item {
        width: parent.width
        height: parent.height
        focus: true  // Ensure the Item can receive key events
        
        Keys.onPressed: {
            if (event.key === Qt.Key_S && event.modifiers & Qt.ControlModifier) {
                saveCurrentNode();
            } else if (event.key === Qt.Key_M && event.modifiers & Qt.ControlModifier) {
                switchMode();
            } else if (event.key === Qt.Key_N && event.modifiers & Qt.ControlModifier) // new note (markdown)
            {
                createNote();
            }
        }

        function switchMode() {
            if (stack.currentItem && stack.currentItem.type === "markdown") {
                if (stack.currentItem.textEdit.textFormat == TextEdit.PlainText) {
                    stack.currentItem.textEdit.textFormat = TextEdit.MarkdownText;
                } else {
                    stack.currentItem.textEdit.textFormat = TextEdit.PlainText;
                }
            }
        }

        function createNote() {
            var component = Qt.createComponent("MarkdownNote.qml");
            var uuid = noteManager.getUuid();
            let name = ""
            let i = 1;
            do {
                name = "Untitled " + i.toString()
                i++
            } while (noteManager.titleExists(name))

            var newNote = component.createObject(stack, {uuid: uuid, title: name, contents: "empty"});
            stack.push(newNote);

            noteManager.createNote(uuid, name, newNote.type);
            listview.reloadNotes();
        }


        function saveCurrentNode() {
            if (stack.currentItem) {
                if (stack.currentItem.type === "markdown") {
                    console.log("save");
                    noteManager.saveNote(stack.currentItem.uuid, stack.currentItem.title, stack.currentItem.contents)
                } else if (stack.currentItem.type === "kanban") {
                    // TODO: Save kanban note
                }
            } else {
                console.error("No current item in the StackView");
            }
            listview.reloadNotes();
        }


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

        StackView {
            id: stack
            anchors.left: listview.right
            anchors.leftMargin: parent.width * 0.05
            anchors.top: parent.top
            anchors.topMargin: 50
            width: parent.width * 0.75
            height: parent.height * 0.95

        }
    }
}
