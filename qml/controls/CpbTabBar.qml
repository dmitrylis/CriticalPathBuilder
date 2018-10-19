import QtQuick 2.11

Item {
    id: root

    property int selectedButton: 0
    
    ListView {
        anchors.fill: parent
        orientation: Qt.Horizontal
        model: 10
        delegate: CpbTabButton {
            checked: selectedButton == index

            onClicked: {
                selectedButton = index
            }
        }
    }
}
