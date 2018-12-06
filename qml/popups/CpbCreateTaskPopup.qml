import QtQuick 2.11
import QtQuick.Controls 2.4

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var row: _popupManager.popupData[0]
    property var column: _popupManager.popupData[1]
    property var parentStory: _popupManager.popupData[2]

    title: qsTr("Create task")

    content: Column {
        anchors.centerIn: parent
        width: parent.width
        spacing: CpbStyle.marginTiny

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbText
            {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Title")
            }

            TextField {
                id: taskTitle

                placeholderText: qsTr("Enter title")
                text: _taskManager.newTaskName(root.parentStory)
            }
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")
            enabled: taskTitle.text !== ""

            onClicked: {
                _taskManager.createTask(taskTitle.text, root.row, root.column, root.parentStory)
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
