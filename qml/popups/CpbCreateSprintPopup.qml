import QtQuick 2.11
import QtQuick.Controls 2.4

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
            text: qsTr("Create Sprint")
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Title")
            }

            TextField {
                id: sprintTitle

                placeholderText: qsTr("Enter title")
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Duration")
            }

            ComboBox {
                id: sprintDuration

                model: [ "Personalidado", "1 week", "2 weeks", "3 weeks", "4 weeks" ]
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Start Date")
            }

            TextField {
                id: sprintStartDate

                inputMask: "00.00.0000"
                maximumLength: 8
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("End Date")
            }

            TextField {
                id: sprintEndDate

                inputMask: "00.00.0000"
                maximumLength: 8
                enabled: sprintDuration.currentIndex == 0
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbButton {
                text: qsTr("OK")

                onClicked: {
                    if (sprintDuration.currentIndex == 0) {
                        _sprintManager.createSprint(sprintTitle.text, sprintStartDate.text, sprintEndDate.text)
                    }
                    else {
                        _sprintManager.createSprint(sprintTitle.text, sprintStartDate.text, sprintDuration.currentIndex)
                    }

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
