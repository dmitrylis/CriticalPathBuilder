import QtQuick 2.11
import QtQuick.Controls 2.4

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var parentSprint: _popupManager.popupData

    title: qsTr("Create story")

    content: Column {
        anchors.centerIn: parent
        width: parent.width
        spacing: CpbStyle.marginTiny

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
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")

            onClicked: {
                _storyManager.createStory(storyTitle.text, root.parentSprint)
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
