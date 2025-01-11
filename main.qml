import QtQuick
import QtQuick.Layouts
import babnote 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property INoteController controller: DBNoteController {}

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
            id: noteExplorerBlock
            Layout.minimumWidth: 200
            Layout.fillWidth: !noteEditorBlock.visible
            Layout.fillHeight: true

            NoteExplorerBar {
                id: noteExplorerBar
                noteController: root.controller
                Layout.fillWidth: true
                Layout.minimumHeight: 25
            }

            NoteExplorer {
                id: noteExplorer
                noteController: root.controller
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        ColumnLayout {
            id: noteEditorBlock
            visible: noteExplorer.noteId != -1
            Layout.fillWidth: true
            Layout.fillHeight: true

            NoteEditor {
                id: noteEditor
                noteController: root.controller
                currentNoteId: noteExplorer.noteId
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
