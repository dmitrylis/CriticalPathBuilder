import QtQuick 2.11
import QtQuick.Window 2.11

import "views"
import "singletons"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Critical Path Builder")

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
        height: 50
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

    CpbPopupView {
        anchors.fill: parent
        visible: _popupManager.popupPath !== ""
    }
}
