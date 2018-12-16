import QtQuick 2.11

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var parentStory: _popupManager.data[0]
    property var row: _popupManager.data[1]
    property var column: _popupManager.data[2]

    title: qsTr("Create task")

    content: Column {
        anchors.centerIn: parent
        spacing: CpbStyle.marginMedium

        CpbTextInput {
            id: taskTitle

            placeholderText: qsTr("Task title")
            text: _taskManager.newTaskName(root.parentStory)
        }

        CpbTextInput {
            id: taskOwner

            placeholderText: qsTr("Task owner")
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")
            enabled: taskTitle.text !== ""

            onClicked: {
                _taskManager.createTask(root.parentStory, taskTitle.text, taskOwner.text, root.row, root.column)
                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
