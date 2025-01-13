import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import noteapp

Window {
    id: root
    width: 640
    height: 480
    visible: true
    color: "#111111"
    title: qsTr("Hello World")

    property INoteController controller: DBNoteController {}

    // Note {
    //     id: testNode
    //     noteId: 10
    //     name: "Unttiled"
    //     type: "markdown"
    //     controller: root.controller
    // }



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
                controller: root.controller
                Layout.minimumHeight: 20
                Layout.fillWidth: true
            }

            FileView {
                id: fileExplorer
                controller: root.controller
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

                StackView {
                    id: stack
                    anchors.fill: parent
                    anchors.topMargin: 20
                    anchors.leftMargin: 20

                    pushEnter: null
                    pushExit: null
                    popEnter: null
                    popExit: null
                }
            }
        }
    }


    Item {
        width: parent.width
        height: parent.height
        focus: true
        
        Keys.onPressed: {
            if (event.key === Qt.Key_N && event.modifiers & Qt.ControlModifier) {
                createNote();
            }
        }
        function createNote() {
            let noteId = root.controller.createNote()
            console.log("created " + noteId.toString())
        }
    }
}
