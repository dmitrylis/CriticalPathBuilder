import QtQuick 2.11
import QtQuick.Controls 2.4

import "../components"
import "../singletons"
import "../effects"

Rectangle {
    clip: true

    Flickable {
        id: hFlickable

        anchors.fill: parent
        contentWidth: storyListView.width
        ScrollBar.horizontal: hScrollbar

        // list view with stories
        ListView {
            id: storyListView

            x: hFlickable.width > storyListView.width ? (hFlickable.width - storyListView.width) / 2 : 0
            width: storyListView.headerItem.width
            height: parent.height
            ScrollBar.vertical: vScrollbar

            displaced: Transition {
                NumberAnimation { properties: "x, y"; easing.overshoot: 1; easing.type: Easing.OutBack }
            }

            headerPositioning: ListView.OverlayHeader

            // days in sprint
            header: CpbDaysView {
                z: 3
                model: _sprintManager.currentSprint ? _sprintManager.currentSprint.daysModel : null
            }

            model: _sprintManager.currentSprint ? _sprintManager.currentSprint.storyModel : null

            delegate: Item {
                id: delegateRoot

                property int visualIndex: index

                width: storyListView.width
                height: mainView.height

                CpbStoryView {
                    id: mainView

                    anchors.horizontalCenter: delegateRoot.horizontalCenter
                    anchors.verticalCenter: delegateRoot.verticalCenter
                    width: delegateRoot.width

                    titleMouseArea {
                        cursorShape: mainView.Drag.active || titleMouseArea.pressed ? Qt.ClosedHandCursor : Qt.OpenHandCursor
                        drag.target: mainView
                        drag.axis: Drag.YAxis
                    }

                    layer.enabled: mainView.Drag.active || mainView.titleMouseArea.pressed
                    layer.effect: CpbShadowEffect {
                        alpha: 0.5
                    }

                    Drag.active: titleMouseArea.drag.active
                    Drag.source: delegateRoot // to pass visualIndex
                    Drag.hotSpot.x: 0 // TODO: this point should be dynamic
                    Drag.hotSpot.y: height / 2

                    states: State {
                        name: "dragged"
                        when: mainView.Drag.active

                        ParentChange {
                            target: mainView
                            parent: storyListView
                        }

                        AnchorChanges {
                            target: mainView
                            anchors.horizontalCenter: undefined
                            anchors.verticalCenter: undefined
                        }

                        PropertyChanges {
                            target: mainView
                            z: 1
                        }
                    }
                }

                DropArea {
                    anchors.fill: parent

                    onEntered: {
                        _storyManager.moveStory(drag.source.visualIndex, delegateRoot.visualIndex, storyRole)
                    }
                }

                states: State {
                    name: "hasDraggedTask"
                    when: _taskManager.draggedTask !== null && _taskManager.draggedTask.parentStory === storyRole

                    PropertyChanges {
                        target: delegateRoot
                        z: 2
                    }
                }
            }
        }
    }

    // scroll bars
    ScrollBar {
        id: hScrollbar

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        z: 1
    }

    ScrollBar {
        id: vScrollbar

        anchors {
            top: parent.top
            bottom: parent.bottom
            topMargin: storyListView.headerItem.height
        }
        x: (hFlickable.width > storyListView.width) ? (storyListView.x + storyListView.width) : (hFlickable.width - width)
        z: 1
    }

    // text stubs
    CpbText {
        anchors.centerIn: parent
        text: qsTr("Click \"Create sprint\" button to create a new sprint")
        fontSize: CpbStyle.fontEnormous
        fontBold: true
        visible: _sprintManager.sprintModel.rowCount === 0
    }

    CpbText {
        anchors.centerIn: parent
        text: qsTr("Click \"Create story\" button to create a new story")
        fontSize: CpbStyle.fontEnormous
        fontBold: true
        visible: _sprintManager.currentSprint !== null &&
                 _sprintManager.currentSprint.storyModel.rowCount === 0
    }

    // temp buttons for testing
    Row {
        anchors {
            bottom: parent.bottom
            left: parent.left
            margins: CpbStyle.marginTiny
        }
        spacing: CpbStyle.marginTiny

        CpbButton {
            text: qsTr("Create sprint")

            onClicked: {
                _popupManager.showCreateSprintPopup()
            }
        }

        CpbButton {
            text: qsTr("Create story")
            visible: _sprintManager.currentSprint !== null

            onClicked: {
                _popupManager.showCreateStoryPopup(_sprintManager.currentSprint)
            }
        }
    }
}
