import QtQuick 2.11

import "../controls"
import "../singletons"

Item {
    id: root
    height: background.height + CpbStyle.marginMedium

    Rectangle {
        id: background

        anchors.centerIn: parent
        width: parent.width - CpbStyle.marginMedium
        height: flickableContent.height
        radius: CpbStyle.marginTiny
        color: "grey"
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
                    delegate: CpbTask {

                    }
                }
            }
        }
    }

    CpbTabButton {
        anchors {
            bottom: root.bottom
            left: root.left
        }
        text: "add task"
        onClicked: {
            _taskManager.createTask(storyRole)
        }
    }
}
