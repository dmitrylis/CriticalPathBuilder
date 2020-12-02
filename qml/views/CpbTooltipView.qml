import QtQuick 2.11

import "../singletons"

Item {
    id: root

    MouseArea {
        anchors.fill: parent
        enabled: !_tooltipManager.autoHide
        visible: enabled

        // blocks propagation of some mouse events
        hoverEnabled: true

        // blocks propagation of some mouse events
        onWheel: { /* do nothing */ }

        // click on dimmed area leads to popup closing
        onClicked: _tooltipManager.hide()
    }

    Loader {
        id: loader

        x: _tooltipManager.position.x
        y: _tooltipManager.position.y
        source: _tooltipManager.path

        onItemChanged: _tooltipManager.updateTooltipPosition(item)
    }
}
