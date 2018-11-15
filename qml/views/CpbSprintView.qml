import QtQuick 2.11

import "../controls"
import "../singletons"

Rectangle {
    clip: true

    // list view with stories
    ListView {
        id: storyListView

        anchors.fill: parent

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
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
                    cursorShape: Qt.OpenHandCursor
                    drag.target: mainView
                    drag.axis: Drag.YAxis
                }

                Drag.active: titleMouseArea.drag.active
                Drag.source: delegateRoot // to pass visualIndex
                Drag.hotSpot.x: width / 2
                Drag.hotSpot.y: height / 2

                states: [
                    State {
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
                            target: mainView.titleMouseArea
                            cursorShape: Qt.ClosedHandCursor
                        }
                    }
                ]
            }

            DropArea {
                anchors.fill: parent

                onEntered: {
                    _storyManager.moveStory(drag.source.visualIndex, delegateRoot.visualIndex, _sprintManager.currentSprint)
                }
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
