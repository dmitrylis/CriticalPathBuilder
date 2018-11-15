import QtQuick 2.11
import QtQuick.Window 2.11

import "controls"
import "views"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        color: "grey"
    }

    CpbSprintTabView {
        id: sprintTabView

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: 50
    }

    CpbSprintView {
        id: sprintView

        anchors {
            left: parent.left
            right: parent.right
            top: sprintTabView.bottom
            bottom: parent.bottom
        }
    }

    // need to move it from here in the future
    Text {
        anchors.centerIn: parent
        text: "Click \"Create sprint\" button to create new sprint"
        visible: _sprintManager.sprintModel.rowCount === 0
    }

    // need to move it from here in the future
    Text {
        anchors.centerIn: parent
        text: "Click \"Create story\" button to create new story"
        visible: _sprintManager.currentSprint !== null &&
                 _sprintManager.currentSprint.storyModel.rowCount === 0
    }

    // temp button for testing
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
