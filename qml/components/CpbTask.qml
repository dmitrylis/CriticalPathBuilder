import QtQuick 2.11

import "../singletons"

Item {
    id: root

    signal removeClicked()

    implicitWidth: CpbStyle.cellWidth
    implicitHeight: CpbStyle.cellHeight

    Rectangle {
        anchors {
            fill: parent
            margins: CpbStyle.marginTiny
        }

        color: CpbStyle.colorBlue
        radius: CpbStyle.marginTiny

        CpbText {
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                leftMargin: CpbStyle.marginSmall
            }

            text: titleRole
            color: CpbStyle.colorWhite
            fontBold: true
        }
    }

    CpbRemoveButton {
        anchors {
            top: parent.top
            right: parent.right
        }
        z: 2

        onClicked: {
            root.removeClicked()
        }
    }
}
