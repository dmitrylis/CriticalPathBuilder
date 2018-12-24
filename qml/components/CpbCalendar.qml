import QtQuick 2.0
import QtQuick.Controls 1.4 as Qt1
import QtQuick.Controls 2.1 as Qt2

Row {
    id: root

    CpbTextInput {
        id: sprintStartDate

        maximumLength: 10
        placeholderText: qsTr("Start Date")
        text: currentDate.toLocaleDateString(locale , Locale.ShortFormat)
    }

    CpbButton {
        id: popupCalendar

        width: 20
        height: 20
        onClicked: popup.open()
    }

    Qt2.Popup {
         id: popup

         x: popupCalendar.x
         y: popupCalendar.y
         z: 2

         padding: 0
         focus: true
         closePolicy: Qt2.Popup.CloseOnEscape | Qt2.Popup.CloseOnPressOutsideParent

         Qt1.Calendar {
             minimumDate: new Date()
             onClicked:
             {
                 sprintStartDate.text = Qt.formatDate(selectedDate, "dd.MM.yyyy")
                 popup.close()
             }
         }
    }
}
