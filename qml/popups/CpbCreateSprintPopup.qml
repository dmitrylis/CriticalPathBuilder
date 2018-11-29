import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQml 2.2

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var locale: Qt.locale()
    property date currentDate: new Date()
    property string dateString

    title: qsTr("Create sprint")

    content: Column {
        anchors.centerIn: parent
        width: parent.width
        spacing: CpbStyle.marginTiny

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Title")
            }

            TextField {
                id: sprintTitle

                placeholderText: qsTr("Enter title")
                text: _sprintManager.newSprintName()
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

                //inputMask: "00.00.0000"
                maximumLength: 10
                text:  currentDate.toLocaleDateString(locale, Locale.ShortFormat)
                //text: Date.fromLocaleDateString(dateString)
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

                //inputMask: "00.00.0000"
                maximumLength: 10
                enabled: sprintDuration.currentIndex == 0
            }
        }
    }

    buttons: [
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
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: {
                _popupManager.hidePopup()
            }
        }
    ]
}
