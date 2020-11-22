import QtQuick 2.11

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var sprintToRemove: _popupManager.data[0]

    title: qsTr("Remove sprint")

    content: CpbText {
        anchors.fill: parent
        text: "Do you really want to remove \"%1\" sprint?".arg(sprintToRemove ? sprintToRemove.title : "")
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")

            onClicked: {
                _sprintManager.removeSprint(sprintToRemove)
                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
