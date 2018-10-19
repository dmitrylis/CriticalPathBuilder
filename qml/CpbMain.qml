import QtQuick 2.11
import QtQuick.Window 2.11

import "controls"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    // back background
    Rectangle {
        anchors.fill: parent
        color: "grey"
    }

    // buttons
    CpbTabBar {
        id: tabBar

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: 50
    }

    // critical path content
    Loader {
        id: content

        anchors {
            left: parent.left
            right: parent.right
            top: tabBar.bottom
            bottom: parent.bottom
        }

        sourceComponent: Rectangle { color: "white" }
    }
}
