import QtQuick 2.15

import com.cpb 1.0

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

        color: {
            switch (typeRole) {
            case Task.DevelopmentTask:
                return CpbStyle.colorBlue
            case Task.QaTask:
                return CpbStyle.colorOrange
            case Task.ResearchTask:
                return CpbStyle.colorCyan
            default:
                return CpbStyle.colorBlue
            }
        }
        radius: CpbStyle.marginTiny

        Column {
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: CpbStyle.marginSmall
            }
            spacing: CpbStyle.marginTiny

            CpbText {
                horizontalAlignment: Text.AlignLeft
                width: parent.width
                text: titleRole
                color: CpbStyle.colorWhite
                fontBold: true
            }

            CpbText {
                horizontalAlignment: Text.AlignLeft
                width: parent.width
                text: ownerRole
                color: CpbStyle.colorLightGrey
                visible: ownerRole !== ""
            }
        }
    }

    CpbRemoveButton {
        anchors {
            top: parent.top
            right: parent.right
        }
        z: 2

        onClicked: root.removeClicked()
    }
}
