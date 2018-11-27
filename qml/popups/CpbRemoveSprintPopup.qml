import QtQuick 2.11

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var sprintToRemove: _popupManager.popupData

    title: qsTr("Remove sprint")

    content: CpbText {
        anchors.fill: parent
        text: sprintToRemove ? sprintToRemove.title : ""
        // to fix strage warning on application closing
        // TypeError: Cannot read property 'title' of null
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")

            onClicked: {
                _sprintManager.removeSprint(sprintToRemove)
                _popupManager.hidePopup()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: {
                _popupManager.hidePopup()
            }
        }
    ]
}
