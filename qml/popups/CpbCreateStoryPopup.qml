import QtQuick 2.11

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

            placeholderText: qsTr("Task title")
            text: _storyManager.newStoryName(root.parentSprint)
        }

        CpbTextInput {
            id: storyOwner

            placeholderText: qsTr("Task owner")
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
