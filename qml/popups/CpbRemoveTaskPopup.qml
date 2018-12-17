import QtQuick 2.11

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var taskToRemove: _popupManager.data[0]

    title: qsTr("Remove task")

    content: CpbText {
        anchors.fill: parent
        text: taskToRemove ? taskToRemove.title : ""
        // to fix strage warning on application closing
        // TypeError: Cannot read property 'title' of null
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")

            onClicked: {
                _taskManager.removeTask(taskToRemove)
                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
