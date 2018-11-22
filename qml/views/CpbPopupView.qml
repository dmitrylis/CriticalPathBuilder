import QtQuick 2.11

import "../singletons"
import "../effects"

MouseArea {
    id: root

    property alias blurSource: blurEffect.source

    // click on dimmed area leads to closing this popup
    onClicked: {
        _popupManager.hidePopup()
    }

    CpbBlurEffect {
        id: blurEffect

        anchors.fill: parent
    }

    Rectangle {
        anchors.fill: parent
        color: CpbStyle.blackColor
        opacity: 0.2
    }

    // auxiliary MouseArea to prevent closing by clicking on popup area
    MouseArea {
        anchors.fill: loader
    }

    Loader {
        id: loader

        anchors.centerIn: parent
        source: _popupManager.popupPath
    }
}
