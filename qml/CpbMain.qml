import QtQuick 2.15
import QtQuick.Window 2.15

import "views"
import "singletons"

Window {
    id: mainWindow

    width: 1024
    height: 768
    minimumWidth: 750
    minimumHeight: 750
    title: qsTr("Critical Path Builder")
    visible: true

    Connections {
        target: _globalManager

        Component.onCompleted: {
            if (_globalManager.showWelcome) {
                _popupManager.showWelcomePopup()
            }
        }

        function onShowWelcomeChanged(showWelcome) {
            if (showWelcome) {
                _popupManager.showWelcomePopup()
            }
        }
    }

    Item {
        id: mainLayer

        anchors.fill: parent

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
