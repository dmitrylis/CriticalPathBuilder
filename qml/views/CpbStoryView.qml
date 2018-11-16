import QtQuick 2.11
import QtQuick.Controls 2.4

import "../controls"
import "../components"
import "../singletons"

Item {
    id: root

    property alias titleMouseArea: titleMouseArea

    height: column.height + CpbStyle.marginMedium

    Column {
        id: column

        anchors.centerIn: parent
        width: parent.width - CpbStyle.marginMedium

        CpbRectangle {
            id: title

            height: 40
            width: parent.width
            color: CpbStyle.greenColor
            radius: [CpbStyle.marginTiny, CpbStyle.marginTiny, 0, 0]

            MouseArea {
                id: titleMouseArea

                anchors.fill: parent
            }

            CpbText {
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                    leftMargin: CpbStyle.marginMedium
                }

                text: titleRole
                color: CpbStyle.whiteColor
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
                    _popupManager.showRemoveStoryPopup(storyRole)
                }
            }
        }

        CpbRectangle {
            id: background

            width: parent.width
            height: flickableContent.height
            radius: [0, 0, CpbStyle.marginTiny, CpbStyle.marginTiny]
            color: CpbStyle.lightGreyColor
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
