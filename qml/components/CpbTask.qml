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




        color: CpbStyle.greenColor
        radius: CpbStyle.marginTiny
    }

    CpbRemoveButton {
        anchors {
            top: parent.top
            right: parent.right
        }

        width: parent.height / 3
        height: parent.height / 3

        onClicked: {
            _popupManager.showRemoveTaskPopup(taskRole)
        }
    }
}
