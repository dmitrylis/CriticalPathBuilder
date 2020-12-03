import QtQuick 2.15

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var parentSprint: _popupManager.data[0]

    title: qsTr("Create story")

    content: Column {
        anchors.centerIn: parent
        spacing: CpbStyle.marginMedium

        CpbTextInput {
            id: storyTitle

            placeholderText: qsTr("Story title")
            text: _storyManager.newStoryName(root.parentSprint)
        }

        CpbEmployeInput {
            id: storyOwner

            placeholderText: qsTr("Story owner")
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")
            enabled: storyTitle.text !== ""

            onClicked: {
                _storyManager.createStory(root.parentSprint, storyTitle.text, storyOwner.text)
                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
