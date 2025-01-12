import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12
import babnote 1.0

ApplicationWindow {
    id: root
    property INoteController controller: DBNoteController {}

    width: 640
    height: 480
    visible: true
    title: qsTr("babnote")

    Material.theme: Material.Dark
    Material.roundedScale: Material.ExtraSmallScale

    function makeid(length) {
        let result = ''
        const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'
        const charactersLength = characters.length
        let counter = 0
        while (counter < length) {
            result += characters.charAt(Math.floor(Math.random(
                                                       ) * charactersLength))
            counter += 1
        }
        return result
    }

    RowLayout {
        anchors.margins: 10
        anchors.fill: parent

        ColumnLayout {
            id: noteExplorerBlock
            Layout.minimumWidth: 200
            Layout.fillWidth: !noteEditorBlock.visible
            Layout.fillHeight: true

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: false

                Button {
                    id: createNoteBtn
                    text: qsTr("Add")
                    onClicked: root.controller.setNoteName(
                                   root.controller.createNote(), makeid(16))
                }
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
            visible: noteEditor.currentNoteId != -1
            Layout.fillWidth: true
            Layout.fillHeight: true

            NoteEditor {
                id: noteEditor
                noteController: root.controller
                currentNoteId: noteExplorer.noteId
                onNoteDeleted: noteExplorer.noteId = -1
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
