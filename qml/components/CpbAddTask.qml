import QtQuick 2.11

import "../singletons"

Item {
    id: root

    signal clicked()

    width: CpbStyle.cellWidth
    height: CpbStyle.cellHeight

    Image {
        anchors.centerIn: parent
        source: "qrc:/images/add_task.png"
        opacity: clickArea.containsMouse ? 1.0 : 0.3
    }

    MouseArea {
        id: clickArea

        anchors {
            fill: parent
            margins: CpbStyle.marginTiny
        }
        hoverEnabled: true

        onClicked: root.clicked()
    }
}
