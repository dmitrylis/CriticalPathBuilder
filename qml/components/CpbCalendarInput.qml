import QtQuick 2.15

CpbTextInput {
    id: root

    property date date: new Date()
    readonly property bool validDate: internal.validDate(date)

    QtObject {
        id: internal

        function dateFromText(text) {
            return Date.fromLocaleDateString(Qt.locale(), text, Locale.ShortFormat)
        }

        function dateToText(date) {
            return date.toLocaleDateString(Locale.ShortFormat)
        }

        function validDate(date) {
            return !isNaN(date.getDate())
        }
    }

    maximumLength: 10

    onTextChanged: {
        root.date = internal.dateFromText(root.text)
    }

    onDateChanged: {
        if (internal.validDate(root.date)) {
            root.text = internal.dateToText(root.date)
        }
    }

    onPressed: {
        const date = internal.validDate(root.date) ? root.date : new Date()
        _tooltipManager.showCalendarTooltip(root, date)
    }
}
