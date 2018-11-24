import QtQuick 2.11
import QtQuick.Controls 2.4 as Controls24
import QtQuick.Controls 1.4 as Controls14

import "../controls"
import "../singletons"
import "../effects"

Rectangle {
    id: root

    //property var sprintAdd: _popupManager.popupData

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
            text: "Create Sprint" // to fix strage warning on application closing
            // TypeError: Cannot read property 'title' of null
        }

        Controls24.TextField {
            id: sprintName
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Enter name")
        }

        Controls24.ComboBox {
            id: sprintDuration
            anchors.horizontalCenter: parent.horizontalCenter
            model: [ "Personalidado", "1 week", "2 weeks", "3 weeks", "4 weeks" ]
        }

        Controls24.TextField {
            id: sprintStartDate
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Enter date")
        }

        Controls24.TextField {
            id: sprintEndDate
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Enter date")
        }

        Controls14.Calendar {

        }

        Row {
            //anchors.centerIn: parent
            anchors.horizontalCenter: parent.horizontalCenter

            Controls24.Button {
                text: "OK"
                onClicked: {
                    _sprintManager.createSprint(sprintName.text)
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
