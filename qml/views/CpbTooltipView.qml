import QtQuick 2.15

import com.cpb 1.0

import "../singletons"

Item {
    id: root

    MouseArea {
        anchors.fill: parent
        enabled: _tooltipManager.policy !== TooltipManager.NonModal
        visible: enabled

        // blocks propagation of some mouse events
        hoverEnabled: true

        // blocks propagation of some mouse events
        onWheel: { /* do nothing */ }

        // click on dimmed area leads to popup closing
        onClicked: {
            if (_tooltipManager.policy !== TooltipManager.StrictlyModal) {
                _tooltipManager.hide()
            }
        }
    }

    Loader {
        id: loader

        x: _tooltipManager.position.x
        y: _tooltipManager.position.y
        source: _tooltipManager.path

        onItemChanged: _tooltipManager.updateTooltipPosition(item)
    }
}
