import QtQuick 2.11
import QtQuick.Controls 2.4

import "../controls"
import "../components"
import "../singletons"
import "../effects"

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
            height: backLayout.height
            radius: [0, 0, CpbStyle.marginTiny, CpbStyle.marginTiny]
            color: CpbStyle.lightGreyColor

            Item {
                id: backLayout

                width: childrenRect.width
                height: childrenRect.height

                Repeater {
                    id: addTaskRepeater

                    model: rowCountRole * columnCountRole
                    delegate: CpbAddTask {
                        property int column: index % columnCountRole
                        property int row: index / columnCountRole

                        x: column * CpbStyle.cellWidth
                        y: row * CpbStyle.cellHeight

                        onClicked: {
                            _taskManager.createTask(row, column, storyRole)
                        }
                    }
                }
            }

            Item {
                id: content

                width: backLayout.width
                height: backLayout.height

                Item {
                    id: highlight

                    x: _taskManager.highlight.x * CpbStyle.cellWidth
                    y: _taskManager.highlight.y * CpbStyle.cellHeight
                    width: _taskManager.highlight.width * CpbStyle.cellWidth
                    height: _taskManager.highlight.height * CpbStyle.cellHeight
                    visible: _taskManager.draggedTask !== null

                    Rectangle {
                        anchors {
                            fill: parent
                            margins: CpbStyle.marginSmall
                        }
                        color: "transparent"
                        border.width: 2
                        border.color: "red"
                    }
                }

                Repeater {
                    model: taskModelRole
                    delegate: CpbTask {
                        id: taskDelegate

                        Behavior on x { NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack; duration: 200 } }
                        Behavior on y { NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack; duration: 200 } }

                        x: columnRole * CpbStyle.cellWidth
                        y: rowRole * CpbStyle.cellHeight

                        layer.enabled: _taskManager.draggedTask === taskRole
                        layer.effect: CpbShadowEffect {
                            alpha: 0.5
                        }

                        onXChanged: {
                            _taskManager.updateHighlightColumn(x, CpbStyle.cellWidth)
                        }

                        onYChanged: {
                            _taskManager.updateHighlightRow(y, CpbStyle.cellHeight)
                        }

                        MouseArea {
                            id: dragArea

                            anchors.fill: parent
                            pressAndHoldInterval: 300
                            cursorShape: _taskManager.draggedTask === taskRole ? Qt.ClosedHandCursor : Qt.OpenHandCursor

                            onPressAndHold: {
                                drag.target = taskDelegate
                                _taskManager.startDragTask(taskRole)
                            }

                            onReleased: {
                                drag.target = null
                                _taskManager.stopDragTask()
                            }
                        }

                        states: State {
                            name: "dragged"
                            when: _taskManager.draggedTask === taskRole

                            PropertyChanges {
                                target: taskDelegate
                                z: 1
                            }
                        }
                    }
                }
            }
        }

        CpbTabButton {
            text: "add row"
            onClicked: {
                _storyManager.addRow(storyRole)
            }
        }
    }
}
