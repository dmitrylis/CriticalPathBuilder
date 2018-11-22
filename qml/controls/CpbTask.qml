import QtQuick 2.11

import "../singletons"

Item {
    width: CpbStyle.cellWidth
    height: CpbStyle.cellHeight

    Rectangle {
        anchors {
            fill: parent
            margins: CpbStyle.marginTiny
        }

        color: CpbStyle.greenColor
    }
}
