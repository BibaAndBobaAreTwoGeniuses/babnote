import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import babnote

Item {
    id: root
    property INoteController noteController
    property int currentNoteId: -1

    signal noteDeleted(int noteId)

    onCurrentNoteIdChanged: resetData()

    function resetData() {
        if (currentNoteId != -1) {
            noteData.name = noteName.text = root.noteController.getNoteName(
                        root.currentNoteId)
            noteData.textFormat = noteTextFormat.setByV(
                        root.noteController.getNoteTextFormat(
                            root.currentNoteId))
            noteData.text = noteText.text = root.noteController.getNoteText(
                        root.currentNoteId)
            noteCreated.text = qsTr(
                        "Created: ") + new Date(root.noteController.getNoteCreationTimestamp(
                                                    currentNoteId)).toString()
            noteUpdated.text = qsTr(
                        "Updated: ") + new Date(root.noteController.getNoteUpdateTimestamp(
                                                    currentNoteId)).toString()
            noteData.tags = noteTags.text = root.noteController.getNoteTags(
                        root.currentNoteId)
        } else {
            noteData.name = noteName.text = ""
            noteData.textFormat = noteTextFormat.setByV(Qt.PlainText)
            noteData.text = noteText.text = ""
            noteCreated.text = ""
            noteUpdated.text = ""
            noteData.tags = noteTags.text = ""
        }
    }

    Item {
        id: noteData
        property string name: ""
        property int textFormat: Qt.PlainText
        property string text: ""
        property string tags: ""
        property bool saved: name == noteName.text
                             && textFormat == noteTextFormat.getCurr()
                             && text == noteText.text && tags == noteTags.text
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        TextField {
            id: noteName
            Layout.fillWidth: true
            placeholderText: qsTr("Name")
        }

        ComboBox {
            id: noteTextFormat
            textRole: "text"
            valueRole: "format"
            popup.modal: true
            model: [{
                    "text": qsTr("Plain text"),
                    "format": Qt.PlainText
                }, {
                    "text": qsTr("Rich text"),
                    "format": Qt.RichText
                }, {
                    "text": qsTr("Auto text"),
                    "format": Qt.AutoText
                }, {
                    "text": qsTr("Markdown text"),
                    "format": Qt.MarkdownText
                }]

            function getCurr() {
                return currentIndex != -1 ? model[currentIndex].format : Qt.PlainText
            }

            function setByV(format) {
                for (var i = 0; i < model.length; ++i) {
                    if (model[i].format === format) {
                        currentIndex = i
                        return i
                    }
                }
                return Qt.PlainText
            }
        }

        TextArea {
            id: noteText
            Layout.fillWidth: true
            Layout.fillHeight: true
            textFormat: noteTextFormat.model[noteTextFormat.currentIndex].format
        }

        TextArea {
            id: noteTags
            Layout.fillWidth: true
            placeholderText: qsTr("Tags")
        }

        Label {
            id: noteCreated
            color: Material.secondaryTextColor
        }

        Label {
            id: noteUpdated
            color: Material.secondaryTextColor
        }

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: qsTr("Delete")
                onClicked: {
                    root.noteController.removeNote(root.currentNoteId)
                    root.noteDeleted(root.currentNoteId)
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Save")
                enabled: !noteData.saved
                onClicked: {
                    root.noteController.setNoteName(root.currentNoteId,
                                                    noteName.text)
                    root.noteController.setNoteText(root.currentNoteId,
                                                    noteText.text)
                    root.noteController.setNoteTextFormat(root.currentNoteId,
                                                          noteText.textFormat)
                    root.noteController.setNoteTags(root.currentNoteId,
                                                    noteTags.text)
                }
            }

            Button {
                text: qsTr("Reset")
                onClicked: root.resetData()
            }
        }
    }
}
