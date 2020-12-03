import QtQuick 2.15

import "../components"
import "../singletons"

Item {
    id: root

    ListView {
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            leftMargin: CpbStyle.marginTiny
            rightMargin: CpbStyle.marginTiny
        }
        height: 50
        spacing: CpbStyle.marginTiny

        displaced: Transition {
            NumberAnimation { properties: "x, y"; easing.overshoot: 1; easing.type: Easing.OutBack }
        }

        orientation: Qt.Horizontal
        model: _sprintManager.sprintModel
        delegate: CpbTabButton {
            checked: _sprintManager.currentSprint === sprintRole
            text: titleRole

            onClicked: _sprintManager.currentSprint = sprintRole

            onRemoveClicked: _popupManager.showRemoveSprintPopup(sprintRole)
        }
    }
}
