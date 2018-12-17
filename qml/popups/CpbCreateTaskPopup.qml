import QtQuick 2.11
import QtQuick.Controls 2.4

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

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Task type")
            }

            ComboBox {
                id: taskType

                property int value: model.get(currentIndex).value

                textRole: "text"

                model: ListModel {
                    ListElement { text: QT_TR_NOOP("Development"); value: Task.DevelopmentTask }
                    ListElement { text: QT_TR_NOOP("Qa"); value: Task.QaTask }
                    ListElement { text: QT_TR_NOOP("Research"); value: Task.ResearchTask }
                }
            }
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
                                        root.column)
                _popupManager.hide()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: _popupManager.hide()
        }
    ]
}
