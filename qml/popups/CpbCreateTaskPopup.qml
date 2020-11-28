import QtQuick 2.11

import com.cpb 1.0

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

        CpbComboBox {
            id: taskType

            property int value: model.get(currentIndex).value

            placeholderText: qsTr("Type")
            textRole: "text"
            model: ListModel {
                ListElement { text: QT_TR_NOOP("Development"); value: Task.DevelopmentTask }
                ListElement { text: QT_TR_NOOP("Qa"); value: Task.QaTask }
                ListElement { text: QT_TR_NOOP("Research"); value: Task.ResearchTask }
            }
        }

        CpbSpinBox {
            id: taskDuration

            value: 1
            from: 1
            to: _taskManager.maxTaskCount(root.parentStory, root.row, root.column)
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")
            enabled: taskTitle.text !== ""

            onClicked: {
                _taskManager.createTask(root.parentStory,
                                        taskTitle.text,
                                        taskOwner.text,
                                        taskType.value,
                                        root.row,
                                        root.column,
                                        taskDuration.value)
                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
