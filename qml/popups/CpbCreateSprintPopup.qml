import QtQuick 2.15

import com.cpb 1.0

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    QtObject {
        id: internal

        property date currentDate: new Date()

        function updateEndDate(date) {
            if (isNaN(date.getDate()) || !sprintDuration.currentData) {
                return
            }

            const duration = sprintDuration.currentData.value
            if (duration !== Sprint.Custom) {
                const newDate = date
                newDate.setDate(newDate.getDate() + (duration + 1) * 7)
                sprintEndDate.date = newDate
            }
        }
    }

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
            textRole: "text"
            model: ListModel {
                ListElement { text: QT_TR_NOOP("1 week"); value: Sprint.OneWeek }
                ListElement { text: QT_TR_NOOP("2 weeks"); value: Sprint.TwoWeeks }
                ListElement { text: QT_TR_NOOP("3 weeks"); value: Sprint.ThreeWeeks }
                ListElement { text: QT_TR_NOOP("4 weeks"); value: Sprint.FourWeeks }
                ListElement { text: QT_TR_NOOP("Custom"); value: Sprint.Custom }
            }

            onCurrentDataChanged: {
                internal.updateEndDate(sprintStartDate.date)
            }
        }

        CpbCalendarInput {
            id: sprintStartDate

            placeholderText: qsTr("Start Date")
            date: internal.currentDate

            onDateChanged: {
                internal.updateEndDate(date)
            }
        }

        CpbCalendarInput {
            id: sprintEndDate

            placeholderText: qsTr("End date")
            enabled: sprintDuration.currentData.value === Sprint.Custom

            Component.onCompleted: {
                internal.updateEndDate(internal.currentDate)
            }
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")
            enabled: sprintTitle.text !== "" && sprintStartDate.validDate && sprintEndDate.validDate && (sprintStartDate.date.getTime() <= sprintEndDate.date.getTime())

            onClicked: {
                _sprintManager.createSprint(sprintTitle.text, sprintStartDate.date, sprintEndDate.date)
                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
