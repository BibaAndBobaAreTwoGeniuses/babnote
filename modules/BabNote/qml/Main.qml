import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import BabNote 1.0
import BabNote.Elements 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    color: "#111111"
    title: qsTr("Hello World")

    property SqlNoteModel noteModel: SqlNoteModel {}

 
    SplitView {
        anchors.fill: parent
        spacing: 100
        handle: Rectangle {
            implicitWidth: 3
            color: SplitHandle.pressed ? "black" : "black"

            border.color: SplitHandle.hovered ? "black" : "black"
            opacity: SplitHandle.pressed ? "1.0" : "0.0"

            Behavior on opacity {
                OpacityAnimator {
                    duration: 500
                }
            }
        }

        ColumnLayout {
            id: fileViewLayout
            spacing: 10
            Layout.minimumWidth: 100
            Layout.maximumWidth: 300
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 5

            FileViewBar {
                noteModel: root.noteModel
                Layout.minimumHeight: 20
                Layout.fillWidth: true
            }

            FileView {
                id: fileExplorer
                noteModel: root.noteModel
                onNoteSelected: noteId => stack.noteId = noteId
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        ColumnLayout {

            id: noteEditorLayout

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 20
            Layout.rightMargin: 20
            Layout.bottomMargin: 20

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Rectangle {
                    id: backgroundRect
                    anchors.fill: parent
                    color: "#222222"
                    radius: 5
                }


                /*TextNote {
                    id: stack
                    noteModel: root.noteModel
                    anchors.fill: parent
                    anchors.topMargin: 20
                    anchors.leftMargin: 20
                }*/
                StackView {
                    id: stack
                    property int noteId
                    anchors.fill: parent
                    anchors.topMargin: 20
                    anchors.leftMargin: 20
                    clip: true

                    onNoteIdChanged: {
                        stack.pop()
                        let comp = Qt.createComponent("TextNote.qml")
                        let obj = comp.createObject(stack, {
                                                        "noteModel": root.noteModel,
                                                        "noteId": noteId,
                                                        "name": root.noteModel.getNoteName(
                                                                    noteId),
                                                        "contents": noteModel.getNoteText(
                                                                        noteId),
                                                        "type": "markdown"
                                                    })
                        stack.push(obj)
                    }
                }
            }
        }
    }

    Item {
        width: parent.width
        height: parent.height
        focus: true

        Keys.onPressed: {
            if (event.key === Qt.Key_N
                    && event.modifiers & Qt.ControlModifier) {
                createNote()
            }
        }
        function createNote() {
            let noteId = root.noteModel.createNote()
            console.log("created " + noteId.toString())
        }
    }
}
