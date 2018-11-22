import QtQuick 2.11
import QtGraphicalEffects 1.0

import "../singletons"

DropShadow {
    id: root

    property real alpha: 1.0

    horizontalOffset: 0
    verticalOffset: 3
    radius: 15
    samples: 2 * radius + 1
    cached: true
    color: Qt.rgba(CpbStyle.blackColor.r,
                   CpbStyle.blackColor.g,
                   CpbStyle.blackColor.b,
                   root.alpha)
}
