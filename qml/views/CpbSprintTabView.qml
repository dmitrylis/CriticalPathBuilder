import QtQuick 2.11
import QtQuick.Controls 2.4

import "../controls"

Item {
    id: root

    ListView {
        anchors.fill: parent
        orientation: Qt.Horizontal
        model: _sprintManager.sprintModel
        delegate: CpbTabButton {
            checked: _sprintManager.currentSprint === sprintRole
            text: titleRole

            onClicked: {
                _sprintManager.currentSprint = sprintRole
            }

            Button {
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }

                text: "x"
                width: 20
                height: 20

                onClicked: {
                    _sprintManager.removeSprint(sprintRole)
                }
            }
        }
    }
}
