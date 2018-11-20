import QtQuick 2.11
import QtQuick.Controls 2.4

import "../controls"
import "../effects"

Rectangle {
    id: root

    property var storyToRemove: _popupManager.popupData

    width: 300
    height: 200

    layer.enabled: true
    layer.effect: CpbShadowEffect {
        alpha: 0.5
    }

    CpbText {
        anchors.horizontalCenter: parent.horizontalCenter
        text: storyToRemove ? storyToRemove.title : "" // to fix strage warning on application closing
                                                       // TypeError: Cannot read property 'title' of null
    }

    Row {
        anchors.centerIn: parent

        Button {
            text: "OK"
            onClicked: {
                _storyManager.removeStory(storyToRemove)
                _popupManager.hidePopup()
            }
        }

        Button {
            text: "CANCEL"
            onClicked: {
                _popupManager.hidePopup()
            }
        }
    }
}