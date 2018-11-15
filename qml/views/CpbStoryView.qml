import QtQuick 2.11
import QtQuick.Controls 2.4

import "../controls"
import "../components"
import "../singletons"

Item {
    id: root

    height: column.height + CpbStyle.marginMedium

    Column {
        id: column

        anchors.centerIn: parent
        width: parent.width - CpbStyle.marginMedium

        CpbRectangle {
            id: title

            height: 50
            width: parent.width
            color: "green"
            radius: [CpbStyle.marginTiny, CpbStyle.marginTiny, 0, 0]

            Text {
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                    leftMargin: CpbStyle.marginTiny
                }

                text: titleRole
                color: "white"
            }

            Button {
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }

                text: "x"
                width: 20
                height: 20

                onClicked: {
                    _storyManager.removeStory(storyRole, _sprintManager.currentSprint)
                }
            }
        }

        CpbRectangle {
            id: background

            width: parent.width
            height: flickableContent.height
            radius: [0, 0, CpbStyle.marginTiny, CpbStyle.marginTiny]
            color: "#F5F5F5"
            clip: true

            Flickable {
                id: flickableContent

                width: parent.width
                height: content.height

                contentWidth: content.width

                Item {
                    id: content

                    width: childrenRect.width
                    height: childrenRect.height

                    Repeater {
                        model: taskModelRole
                        delegate: CpbTask {}
                    }
                }
            }
        }

        CpbTabButton {
            text: "add task"
            onClicked: {
                _taskManager.createTask(storyRole)
            }
        }
    }
}
