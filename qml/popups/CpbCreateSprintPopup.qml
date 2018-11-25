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
            text: "Create Sprint"
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: "Name"
            }
            Controls24.TextField {
                id: sprintName
                placeholderText: qsTr("Enter name")
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: "Duration"
            }
            Controls24.ComboBox {
                id: sprintDuration
                model: [ "Personalidado", "1 week", "2 weeks", "3 weeks", "4 weeks" ]
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: "Start Date"
            }
            Controls24.TextField {
                id: sprintStartDate
                inputMask: "00.00.0000"
                maximumLength: 8
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: "End Date"
            }
            Controls24.TextField {
                id: sprintEndDate
                inputMask: "00.00.0000"
                maximumLength: 8
                enabled: sprintDuration.currentIndex == 0 ? true : false
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            Controls24.Button {
                text: "OK"
                onClicked: {
                    if (sprintDuration.currentIndex == 0)
                        _sprintManager.createSprint(sprintName.text, sprintStartDate.text, sprintEndDate.text)
                    else
                        _sprintManager.createSprint(sprintName.text, sprintStartDate.text, sprintDuration.currentIndex)
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
