import QtQuick 2.11

import "../singletons"

MouseArea {
    id: root

    // click on dimmed area leads to closing this popup
    onClicked: {
        _popupManager.hidePopup()
    }

    Rectangle {
        anchors.fill: parent
        color: CpbStyle.blackColor
        opacity: 0.3
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
