import QtQuick 2.11
import QtQuick.Controls 2.4

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var parentSprint: _popupManager.popupData[0]

    title: qsTr("Create story")

    content: Column {
        anchors.centerIn: parent
        width: parent.width
        spacing: CpbStyle.marginTiny

        Column {
            Row {
                anchors.horizontalCenter: parent.horizontalCenter

                CpbText
                {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Title")
                }

                TextField {
                    id: storyTitle

                    placeholderText: qsTr("Enter title")
                    text: _storyManager.newStoryName(root.parentSprint)
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter

                CpbText
                {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Owner")
                }

                TextField {
                    id: storyOwner

                    placeholderText: qsTr("Enter owner")
                }
            }
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")
            enabled: storyTitle.text !== ""

            onClicked: {
                _storyManager.createStory(root.parentSprint, storyTitle.text, storyOwner.text)
                _popupManager.hidePopup()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: {
                _popupManager.hidePopup()
            }
        }
    ]
}
