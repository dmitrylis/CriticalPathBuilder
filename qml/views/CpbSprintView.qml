import QtQuick 2.11

Rectangle {
    clip: true

    ListView {
        id: root
        anchors.fill: parent

        displaced: Transition {
                NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
            }

        model: _sprintManager.currentSprint ? _sprintManager.currentSprint.storyModel : null
        delegate: MouseArea {
            id: delegateRoot

            property int visualIndex: model.index

            width: ListView.view.width
            height: icon.height

            drag.target: icon
            drag.axis: Drag.YAxis


            CpbStoryView {
                id: icon
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                enabled: false

                Drag.active: delegateRoot.drag.active
                Drag.source: delegateRoot
                Drag.hotSpot.x: width/2
                Drag.hotSpot.y: height/2

                states: [
                    State {
                        when: icon.Drag.active
                        ParentChange {
                            target: icon
                            parent: root
                        }

                        AnchorChanges {
                            target: icon
                            anchors.horizontalCenter: undefined
                            anchors.verticalCenter: undefined
                        }
                    }

                ]
            }

            DropArea {
                anchors {
                    fill: parent
                    margins: 10
                }

                onEntered: _storyManager.moveStory(drag.source.visualIndex, delegateRoot.visualIndex, _sprintManager.currentSprint)
            }

        }
    }
}
