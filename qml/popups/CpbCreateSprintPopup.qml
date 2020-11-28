import QtQuick 2.11

import com.cpb 1.0

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    QtObject {
        id: internal

        property date currentDate: new Date()

        function validDate(date) {
            return !isNaN(date.getDate())
        }

        function validDateString(dateString) {
            return validDate(dateFromString(dateString))
        }

        function dateToString(date) {
            return date.toLocaleDateString(Locale.ShortFormat)
        }

        function dateFromString(dateString) {
            return Date.fromLocaleDateString(Qt.locale(), dateString, Locale.ShortFormat)
        }

        function updateEndDate(date) {
            if (!validDate(date) || !sprintDuration.currentData) {
                return
            }

            const duration = sprintDuration.currentData.value
            if (duration !== Sprint.Custom) {
                const newDate = date
                newDate.setDate(newDate.getDate() + (duration + 1) * 7)
                sprintEndDate.text = dateToString(newDate)
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
                internal.updateEndDate(internal.dateFromString(sprintStartDate.text))
            }
        }

        CpbTextInput {
            id: sprintStartDate

            maximumLength: 10
            placeholderText: qsTr("Start Date")
            text: internal.dateToString(internal.currentDate)

            onTextEdited: {
                internal.updateEndDate(internal.dateFromString(text))
            }
        }

        CpbTextInput {
            id: sprintEndDate

            placeholderText: qsTr("End date")
            maximumLength: 10
            enabled: sprintDuration.currentData.value === Sprint.Custom

            Component.onCompleted: {
                internal.updateEndDate(internal.currentDate)
            }
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")
            enabled: sprintTitle.text !== "" && internal.validDateString(sprintStartDate.text) && internal.validDateString(sprintEndDate.text)

            onClicked: {
                _sprintManager.createSprint(sprintTitle.text, internal.dateFromString(sprintStartDate.text), internal.dateFromString(sprintEndDate.text))
                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
