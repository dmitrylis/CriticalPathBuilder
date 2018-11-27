import QtQuick 2.11

import "../singletons"

Item {
    implicitWidth: CpbStyle.cellWidth
    implicitHeight: CpbStyle.cellHeight

    Rectangle {
        anchors {
            fill: parent
            margins: CpbStyle.marginTiny
        }

        color: CpbStyle.greenColor
        radius: CpbStyle.marginTiny

        CpbText {
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                leftMargin: CpbStyle.marginSmall
            }

            text: titleRole
            color: CpbStyle.whiteColor
            fontBold: true
        }
    }

    CpbRemoveButton {
        anchors {
            top: parent.top
            right: parent.right
        }

        onClicked: {
            _popupManager.showRemoveTaskPopup(taskRole)
        }
    }
}
