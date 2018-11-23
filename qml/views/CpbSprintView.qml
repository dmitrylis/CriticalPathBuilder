import QtQuick 2.11
import QtQuick.Controls 2.4

import "../controls"
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
                z: 100
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
        active: true
        z: 1
    }

    ScrollBar {
        id: vScrollbar

        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            topMargin: storyListView.headerItem.height
        }
        active: true
        z: 1
    }

    // text stubs
    CpbText {
        anchors.centerIn: parent
        text: "Click \"Create sprint\" button to create new sprint"
        fontSize: CpbStyle.fontHuge
        visible: _sprintManager.sprintModel.rowCount === 0
    }

    CpbText {
        anchors.centerIn: parent
        text: "Click \"Create story\" button to create new story"
        fontSize: CpbStyle.fontHuge
        visible: _sprintManager.currentSprint !== null &&
                 _sprintManager.currentSprint.storyModel.rowCount === 0
    }

    // temp buttons for testing
    CpbTabButton {
        id: cpdbutt

        anchors.bottom: parent.bottom
        text: "Create sprint"

        onClicked: {
            _sprintManager.createSprint()
        }
    }

    CpbTabButton {
        anchors {
            bottom: parent.bottom
            left: cpdbutt.right
        }
        text: "Create story"
        visible: _sprintManager.currentSprint !== null

        onClicked: {
            _storyManager.createStory(_sprintManager.currentSprint)
        }
    }
}
