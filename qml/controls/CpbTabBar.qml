import QtQuick 2.11

Item {
    id: root

    property int selectedButton: 0

    ListView {
        anchors.fill: parent
        orientation: Qt.Horizontal
        model: _sprintModel
        delegate: CpbTabButton {
            checked: selectedButton == index
            text: model.titleRole

            onClicked: {
                selectedButton = index
            }
        }
    }
}
