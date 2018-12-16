import QtQuick 2.11
import QtQuick.Controls 2.4

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var locale: Qt.locale()
    property date currentDate: new Date()

    height: 400
    title: qsTr("Create sprint")

    content: Column {
        anchors.centerIn: parent
        spacing: CpbStyle.marginMedium

        CpbTextInput {
            id: sprintTitle

            placeholderText: qsTr("Sprint title")
            text: _sprintManager.newSprintName()
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

        CpbTextInput {
            id: sprintStartDate

            maximumLength: 10
            placeholderText: qsTr("Start Date")
            text: currentDate.toLocaleDateString(locale , Locale.ShortFormat)
        }

        CpbTextInput {
            id: sprintEndDate

            placeholderText: qsTr("End date")
            text: currentDate.toLocaleDateString(locale, Locale.ShortFormat)
            maximumLength: 10
            enabled: sprintDuration.currentIndex == 0
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")
            enabled: sprintTitle.text !== "" && sprintStartDate.text !== "" && (sprintEndDate.text !== "" || sprintDuration.currentIndex !== 0)

            onClicked: {
                if (sprintDuration.currentIndex == 0) {
                    _sprintManager.createSprint(sprintTitle.text, sprintStartDate.text, sprintEndDate.text)
                }
                else {
                    _sprintManager.createSprint(sprintTitle.text, sprintStartDate.text, sprintDuration.currentIndex)
                }

                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
