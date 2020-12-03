import QtQuick 2.15
import QtGraphicalEffects 1.12

import "../singletons"

DropShadow {
    id: root

    property real alpha: 1.0

    horizontalOffset: 0
    verticalOffset: 3
    radius: 15
    samples: 2 * radius + 1
    cached: true
    color: Qt.rgba(CpbStyle.colorBlack.r,
                   CpbStyle.colorBlack.g,
                   CpbStyle.colorBlack.b,
                   root.alpha)
}
