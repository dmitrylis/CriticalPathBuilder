import QtQuick 2.11

import "../controls"

Item {
    id: root

    ListView {
        anchors.fill: parent
        orientation: Qt.Horizontal
        model: _sprintManager.sprintModel
        delegate: CpbTabButton {
            checked: _sprintManager.currentSprint == index
            text: model.titleRole

            onClicked: {
                _sprintManager.currentSprint = index
            }
        }
    }
}
