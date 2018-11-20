import QtQuick 2.11

import "../controls"
import "../singletons"
import "../effects"

Rectangle {
    id: root

    clip: true

    // list view with stories
    ListView {
        id: storyListView

        width: storyListView.headerItem.width
        height: parent.height

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
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
                Drag.hotSpot.x: width / 2
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

        states: State {
            name: "centered"
            when: root.width > storyListView.width

            AnchorChanges {
                target: storyListView
                anchors.horizontalCenter: root.horizontalCenter
            }
        }
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
