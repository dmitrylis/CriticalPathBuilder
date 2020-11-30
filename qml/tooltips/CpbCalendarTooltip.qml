import QtQuick 2.11
import QtQuick.Controls 1.4

import com.cpb 1.0

import "../components"
import "../effects"
import "../singletons"

Item {
    id: root

    property var sourceDate: _tooltipManager.data[0]

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
            _tooltipManager.senderItem().text = selectedDate.toLocaleDateString(Locale.ShortFormat)
            _tooltipManager.hide()
        }
    }
}
