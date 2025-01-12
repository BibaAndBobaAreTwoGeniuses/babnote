import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import babnote

Item {
    id: root
    property INoteController noteController

    RowLayout {
        anchors.fill: parent

        Button {
            id: createNoteBtn
            text: qsTr("Add")
            onClicked: root.noteController.setNoteName(
                           root.noteController.createNote(), makeid(16))
        }
    }

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
}
