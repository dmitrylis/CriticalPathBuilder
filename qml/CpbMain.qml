import QtQuick 2.15
import QtQuick.Window 2.15

import "views"
import "singletons"

Window {
    id: mainWindow

    width: 800
    height: 600
    minimumWidth: 460
    minimumHeight: 700
    title: qsTr("Critical Path Builder")
    visible: true

    CpbWelcomeView {
        id: welcomeLayer

        anchors.fill: parent
        visible: _globalManager.showWelcome
    }

    Item {
        id: mainLayer

        anchors.fill: parent
        visible: !_globalManager.showWelcome

        Rectangle {
            anchors.fill: parent
            color: CpbStyle.colorDarkGrey
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
        visible: !!_popupManager.path
    }

    CpbTooltipView {
        id: tooltipLayer

        anchors.fill: parent
        visible: !!_tooltipManager.path
    }
}
