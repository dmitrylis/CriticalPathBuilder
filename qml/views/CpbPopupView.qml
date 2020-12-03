import QtQuick 2.15

import "../singletons"
import "../effects"

MouseArea {
    id: root

    property alias blurSource: blurEffect.source

    // blocks propagation of some mouse events
    hoverEnabled: true

    // blocks propagation of some mouse events
    onWheel: { /* do nothing */ }

    // click on dimmed area leads to closing this popup
    onClicked: _popupManager.hide()

    CpbBlurEffect {
        id: blurEffect

        anchors.fill: parent
    }

    Rectangle {
        anchors.fill: parent
        color: CpbStyle.colorBlack
        opacity: 0.2
    }

    // auxiliary MouseArea to prevent closing by clicking on popup area
    MouseArea {
        anchors.fill: loader
    }

    Loader {
        id: loader

        anchors.centerIn: parent
        source: _popupManager.path
    }
}
