import QtQuick 2.15

import QtQuick.Controls 2.15

import "../components"

CpbBasePopup {
    id: root

    width: 700
    height: 700
    title: qsTr("Settings")
    closeButtonVisible: true

    content: Column {
        anchors.centerIn: parent

        Switch {
            text: qsTr("Theme: %1").arg(checked ? "Light" : "Dark")
        }

        CpbButton {
            text: "show welcome"

            onClicked: _globalManager.setShowWelcome(true)
        }

    }
}
