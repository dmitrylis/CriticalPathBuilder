import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.12

import "../singletons"
import "../components"
import "../effects"

CpbRectangle {
    id: root

    width: _tooltipManager.senderItem.width
    height: view.height
    radius: [0, 0, CpbStyle.marginTiny, CpbStyle.marginTiny]
    layer.enabled: true
    layer.effect: CpbShadowEffect {
        alpha: 0.5
    }

    ListView {
        id: view

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: CpbRectangle {
                width: view.width
                height: view.height
                radius: root.radius
            }
        }

        width: parent.width
        implicitHeight: contentHeight
        model: ["Dmitry Lisin", "Christoph Waltz", "Jesse Pinkman", "Walter White", "Dr. Baxter Stockman"]
        delegate: ItemDelegate {
            width: root.width
            height: _tooltipManager.senderItem.height
            highlighted: hovered

            contentItem: CpbText {
                horizontalAlignment: Text.AlignLeft
                text: modelData
            }

            onClicked: {
                _tooltipManager.senderItem.text = modelData
                _tooltipManager.hide()
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
