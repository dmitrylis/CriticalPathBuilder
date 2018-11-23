import QtQuick 2.11

import "../components"
import "../singletons"

Item {
    id: root

    ListView {
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 50
        spacing: CpbStyle.marginTiny

        orientation: Qt.Horizontal
        model: _sprintManager.sprintModel
        delegate: CpbTabButton {
            checked: _sprintManager.currentSprint === sprintRole
            text: titleRole

            onClicked: {
                _sprintManager.currentSprint = sprintRole
            }

            onRemoveClicked: {
                _popupManager.showRemoveSprintPopup(sprintRole)
            }
        }
    }
}
