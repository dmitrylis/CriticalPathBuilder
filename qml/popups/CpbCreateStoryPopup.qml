import QtQuick 2.11
import QtQuick.Controls 2.4

import "../singletons"
import "../effects"
import "../components"

Rectangle {
    id: root

    property var parentSprint: _popupManager.popupData

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
            text: qsTr("Create Story")
        }

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
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbButton {
                text: qsTr("OK")

                onClicked: {
                    _storyManager.createStory(storyTitle.text, root.parentSprint)
                    _popupManager.hidePopup()
                }
            }

            CpbButton {
                text: qsTr("CANCEL")

                onClicked: {
                    _popupManager.hidePopup()
                }
            }
        }
    }
}
