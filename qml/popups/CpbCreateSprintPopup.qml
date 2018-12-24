import QtQuick 2.11
import QtQuick.Controls 2.1

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

        CpbComboBox {
            id: sprintDuration

            placeholderText: qsTr("Duration")
            model: [ "Personalidado", "1 week", "2 weeks", "3 weeks", "4 weeks" ]
        }

        CpbCalendar {
            id: sprintStartDate
        }

        CpbCalendar {
            id: sprintEndDate
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
