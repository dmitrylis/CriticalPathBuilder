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

    // temp button for testing
    CpbTabButton {
        anchors {
            bottom: parent.bottom
        }
        text: "add sprint"
        onClicked: {
            _sprintManager.addSprint()
        }
    }
}
