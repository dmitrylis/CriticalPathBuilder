import QtQuick 2.15

import com.cpb 1.0

import "../components"
import "../singletons"
import "../effects"

Item {
    id: root

    property alias titleMouseArea: titleMouseArea
    property Flickable parentFlickable: null

    height: columnPositioner.height + _themeManager.sizes.medium

    Column {
        id: columnPositioner

        anchors.centerIn: parent
        width: parent.width - _themeManager.sizes.medium

        CpbRectangle {
            id: title

            height: 40
            width: parent.width
            color: CpbStyle.colorGreen
            radius: [_themeManager.sizes.tiny, _themeManager.sizes.tiny, 0, 0]

            MouseArea {
                id: titleMouseArea

                anchors.fill: parent
            }

            Row {
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                    leftMargin: _themeManager.sizes.medium
                }

                spacing: _themeManager.sizes.small

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
                    rightMargin: !parentFlickable.atXEnd && (root.width > mainWindow.width) ? (root.width - mainWindow.width - parentFlickable.contentX) : _themeManager.sizes.tiny
                    verticalCenter: parent.verticalCenter
                }

                onClicked: _popupManager.showRemoveStoryPopup(storyRole)
            }
        }

        CpbRectangle {
            id: background

            width: parent.width
            height: backLayout.height
            radius: [0, 0, _themeManager.sizes.tiny, _themeManager.sizes.tiny]
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

                        x: column * _themeManager.sizes.cellWidth
                        y: row * _themeManager.sizes.cellHeight

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

                    x: _taskManager.highlight.x * _themeManager.sizes.cellWidth
                    y: _taskManager.highlight.y * _themeManager.sizes.cellHeight
                    width: _taskManager.highlight.width * _themeManager.sizes.cellWidth
                    height: _taskManager.highlight.height * _themeManager.sizes.cellHeight
                    visible: _taskManager.draggedTask !== null && _taskManager.draggedTask.parentStory === storyRole

                    Rectangle {
                        anchors {
                            fill: parent
                            margins: _themeManager.sizes.small
                        }
                        color: CpbStyle.colorTransparent
                        border.width: 2
                        border.color: _taskManager.dropPossible ? "green" : "red"
                        radius: _themeManager.sizes.tiny
                    }
                }

                Repeater {
                    model: taskModelRole

                    delegate: CpbTask {
                        id: taskDelegate

                        x: columnRole * _themeManager.sizes.cellWidth
                        y: rowRole * _themeManager.sizes.cellHeight
                        visible: rowRole < rowCountRole

                        Binding {
                            target: taskDelegate
                            property: "width"
                            value: daysCountRole * _themeManager.sizes.cellWidth
                        }

                        layer.enabled: _taskManager.draggedTask === taskRole
                        layer.effect: CpbShadowEffect {
                            alpha: 0.5
                        }

                        Behavior on x { enabled: _taskManager.draggedTask === null; NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack } }
                        Behavior on y { enabled: _taskManager.draggedTask === null; NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack } }
                        Behavior on width { enabled: _taskManager.draggedTask === null; NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack } }

                        onXChanged: _taskManager.updateHighlightColumn(x, _themeManager.sizes.cellWidth)

                        onYChanged: _taskManager.updateHighlightRow(y, _themeManager.sizes.cellHeight)

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

                                var rightEdge = Math.max(resArea.x + resArea.width, _themeManager.sizes.cellWidth / 2)
                                taskDelegate.width = rightEdge

                                _taskManager.updateHighlightDaysCount(rightEdge, _themeManager.sizes.cellWidth)
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
            height: _themeManager.sizes.tiny
            width: _themeManager.sizes.tiny
        }

        Row {
            anchors.right: parent.right
            anchors.rightMargin: !parentFlickable.atXEnd && (root.width > mainWindow.width) ? (root.width - mainWindow.width - parentFlickable.contentX) : 0
            spacing: _themeManager.sizes.tiny

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
