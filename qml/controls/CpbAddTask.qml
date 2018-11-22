import QtQuick 2.11

import "../singletons"

Item {
    id: root

    signal clicked()

    width: CpbStyle.cellWidth
    height: CpbStyle.cellHeight

    Rectangle {
        anchors {
            fill: parent
            margins: CpbStyle.marginTiny
        }

        color: CpbStyle.greyColor

        MouseArea {
            id: clickArea

            anchors.fill: parent

            onClicked: root.clicked()
        }
    }
}
