import QtQuick 2.11

import "../components"
import "../singletons"
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
        spacing: CpbStyle.marginTiny

        CpbButton {
            text: qsTr("OK")

            onClicked: {
                _storyManager.removeStory(storyToRemove)
                _popupManager.hidePopup()
            }
        }

        CpbButton {
            text: qsTr("CANCEL")

            onClicked: {
                _popupManager.hidePopup()
            }
        }
    }
}
