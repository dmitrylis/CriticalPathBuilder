import QtQuick 2.11
import QtQuick.Window 2.11

import "views"
import "singletons"

Window {
    visible: true
    minimumWidth: 400
    minimumHeight: 300
    width: 800
    height: 600
    title: qsTr("Critical Path Builder")

    Item {
        id: mainLayer

        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: CpbStyle.darkGreyColor
        }

        CpbSprintTabView {
            id: sprintTabView

            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            height: 50 + CpbStyle.marginTiny
        }

        CpbSprintView {
            id: sprintView

            anchors {
                left: parent.left
                right: parent.right
                top: sprintTabView.bottom
                bottom: parent.bottom
            }
        }
    }

    CpbPopupView {
        id: popupLayer

        anchors.fill: parent
        blurSource: mainLayer
        visible: _popupManager.popupPath !== ""
    }
}
