import QtQuick 2.15
import QtQuick.Controls 1.4

import com.cpb 1.0

import "../components"
import "../effects"
import "../singletons"

Item {
    id: root

    property date sourceDate: _tooltipManager.data[0]

    width: calendar.width
    height: calendar.height + CpbStyle.marginTiny * 2

    Calendar {
        id: calendar

        width: 300
        height: 300
        selectedDate: root.sourceDate
        layer.enabled: true
        layer.effect: CpbShadowEffect {
            alpha: 0.5
        }

        onClicked: {
            _tooltipManager.senderItem.date = selectedDate
            _tooltipManager.hide()
        }
    }

    Connections {
        target: _tooltipManager.senderItem

        function onDateChanged() {
            const date = _tooltipManager.senderItem.date
            if (!isNaN(date.getDate())) {
                calendar.selectedDate = date
            }
            else {
                calendar.selectedDate = new Date()
            }
        }
    }

    Connections {
        target: mainWindow

        function onWidthChanged() {
            _tooltipManager.updateTooltipPosition(root)
        }

        function onHeightChanged() {
            _tooltipManager.updateTooltipPosition(root)
        }
    }
}
