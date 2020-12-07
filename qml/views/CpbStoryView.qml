import QtQuick 2.15

import com.cpb 1.0

import "../components"
import "../singletons"
import "../effects"

Item {
    id: root

    property alias titleMouseArea: titleMouseArea
    property Flickable parentFlickable: null

    height: columnPositioner.height + CpbStyle.marginMedium

    Column {
        id: columnPositioner

        anchors.centerIn: parent
        width: parent.width - CpbStyle.marginMedium

        CpbRectangle {
            id: title

            height: 40
            width: parent.width
            color: CpbStyle.colorGreen
            radius: [CpbStyle.marginTiny, CpbStyle.marginTiny, 0, 0]

            MouseArea {
                id: titleMouseArea

                anchors.fill: parent
            }

            Row {
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                    leftMargin: CpbStyle.marginMedium
                }

                spacing: CpbStyle.marginSmall

                CpbText {
                    text: titleRole
                    color: CpbStyle.colorWhite
                    fontBold: true
                }

                CpbText {
                    text: ownerRole
                    color: CpbStyle.colorLightGrey
                }
            }

            CpbRemoveButton {
                anchors {
                    right: parent.right
                    rightMargin: !parentFlickable.atXEnd && (root.width > mainWindow.width) ? (root.width - mainWindow.width - parentFlickable.contentX) : CpbStyle.marginTiny
                    verticalCenter: parent.verticalCenter
                }

                onClicked: _popupManager.showRemoveStoryPopup(storyRole)
            }
        }

        CpbRectangle {
            id: background

            width: parent.width
            height: backLayout.height
            radius: [0, 0, CpbStyle.marginTiny, CpbStyle.marginTiny]
            color: CpbStyle.colorLightGrey
            z: 1

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

                        onClicked: _popupManager.showCreateTaskPopup(storyRole, row, column)
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
                    visible: _taskManager.draggedTask !== null && _taskManager.draggedTask.parentStory === storyRole

                    Rectangle {
                        anchors {
                            fill: parent
                            margins: CpbStyle.marginSmall
                        }
                        color: CpbStyle.colorTransparent
                        border.width: 2
                        border.color: _taskManager.dropPossible ? "green" : "red"
                        radius: CpbStyle.marginTiny
                    }
                }

                Repeater {
                    model: taskModelRole

                    delegate: CpbTask {
                        id: taskDelegate

                        x: columnRole * CpbStyle.cellWidth
                        y: rowRole * CpbStyle.cellHeight
                        visible: rowRole < rowCountRole

                        Binding {
                            target: taskDelegate
                            property: "width"
                            value: daysCountRole * CpbStyle.cellWidth
                        }

                        layer.enabled: _taskManager.draggedTask === taskRole
                        layer.effect: CpbShadowEffect {
                            alpha: 0.5
                        }

                        Behavior on x { enabled: _taskManager.draggedTask === null; NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack } }
                        Behavior on y { enabled: _taskManager.draggedTask === null; NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack } }
                        Behavior on width { enabled: _taskManager.draggedTask === null; NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack } }

                        onXChanged: _taskManager.updateHighlightColumn(x, CpbStyle.cellWidth)

                        onYChanged: _taskManager.updateHighlightRow(y, CpbStyle.cellHeight)

                        onRemoveClicked: _popupManager.showRemoveTaskPopup(taskRole)

                        MouseArea {
                            id: dragArea

                            anchors.fill: parent
                            cursorShape: Qt.OpenHandCursor
                            drag.target: taskDelegate
                            hoverEnabled: true

                            onEntered: {
                                if (_taskManager.draggedTask === null) {
                                    _tooltipManager.showTaskDescriptionTooltip(dragArea, taskRole)
                                }
                            }

                            onExited: _tooltipManager.hide()

                            onPressed: {
                                _tooltipManager.hide()
                                _taskManager.startDragTask(taskRole, TaskManager.GestureMove)
                            }

                            onReleased: _taskManager.stopDragTask()
                        }

                        MouseArea {
                            id: resArea

                            x: parent.width - width
                            width: 15
                            height: parent.height
                            cursorShape: Qt.SizeHorCursor

                            drag.axis: Drag.XAxis
                            drag.target: resArea

                            onPressed: {
                                _tooltipManager.hide()
                                _taskManager.startDragTask(taskRole, TaskManager.GestureResizeX)
                            }

                            onXChanged: {
                                if (_taskManager.draggedTask === null) {
                                    return
                                }

                                var rightEdge = Math.max(resArea.x + resArea.width, CpbStyle.cellWidth / 2)
                                taskDelegate.width = rightEdge

                                _taskManager.updateHighlightDaysCount(rightEdge, CpbStyle.cellWidth)
                            }

                            onReleased: _taskManager.stopDragTask()

                            onCanceled: _taskManager.stopDragTask()
                        }

                        states: State {
                            name: "dragged"
                            when: _taskManager.draggedTask === taskRole

                            PropertyChanges {
                                target: highlight
                                z: 1
                            }

                            PropertyChanges {
                                target: taskDelegate
                                opacity: 0.7
                                z: 2
                            }
                        }
                    }
                }
            }
        }

        // spacer
        Item {
            height: CpbStyle.marginTiny
            width: CpbStyle.marginTiny
        }

        Row {
            anchors.right: parent.right
            anchors.rightMargin: !parentFlickable.atXEnd && (root.width > mainWindow.width) ? (root.width - mainWindow.width - parentFlickable.contentX) : 0
            spacing: CpbStyle.marginTiny

            CpbText {
                anchors.verticalCenter: parent.verticalCenter
                text: rowCountRole <= _storyManager.maxTaskRow(storyRole) ? qsTr("some tasks are hidden") : ""
                color: CpbStyle.colorBlue
                fontBold: true
            }

            CpbButton {
                width: 75
                height: 30
                text: "▼"
                enabled: rowCountRole !== _storyManager.maxRowCount()

                onClicked: _storyManager.addRow(storyRole)
            }

            CpbButton {
                width: 75
                height: 30
                text: "▲"
                enabled: rowCountRole !== _storyManager.minRowCount()

                onClicked: _storyManager.removeRow(storyRole)
            }
        }
    }
}
