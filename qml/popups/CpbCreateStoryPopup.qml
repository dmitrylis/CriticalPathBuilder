import QtQuick 2.11
import QtQuick.Controls 2.4 as Controls24
import QtQuick.Controls 1.4 as Controls14

import "../controls"
import "../singletons"
import "../effects"
import "../components"

Rectangle {
    id: root
    width: 300
    height: 300
    layer.enabled: true
    layer.effect: CpbShadowEffect {
        alpha: 0.5
    }

    Column {
        anchors.centerIn: parent
        width: parent.width
        spacing: CpbStyle.marginTiny

        CpbText {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Create Story"
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            CpbText
            {
                anchors.verticalCenter: parent.verticalCenter
                text: "Name"
            }

        Controls24.TextField {
            id: storyName
            placeholderText: qsTr("Enter name")
        }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            Controls24.Button {
                text: "OK"
                onClicked: {
                    _storyManager.createStory(_sprintManager.currentSprint, storyName.text)
                    _popupManager.hidePopup()
                }
            }

            Controls24.Button {
                text: "CANCEL"
                onClicked: {
                    _popupManager.hidePopup()
                }
            }
        }
    }
}
