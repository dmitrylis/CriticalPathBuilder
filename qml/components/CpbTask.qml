import QtQuick 2.15

import com.cpb 1.0

import "../singletons"

Item {
    id: root

    signal removeClicked()

    implicitWidth: _themeManager.sizes.cellWidth
    implicitHeight: _themeManager.sizes.cellHeight

    Rectangle {
        anchors {
            fill: parent
            margins: _themeManager.sizes.tiny
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
        radius: _themeManager.sizes.tiny

        Column {
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: _themeManager.sizes.small
            }
            spacing: _themeManager.sizes.tiny

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
