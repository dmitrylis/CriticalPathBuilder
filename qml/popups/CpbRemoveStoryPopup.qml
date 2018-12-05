import QtQuick 2.11

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    property var storyToRemove: _popupManager.popupData[0]

    title: qsTr("Remove story")

    content: CpbText {
        anchors.fill: parent
        text: storyToRemove ? storyToRemove.title : ""
        // to fix strage warning on application closing
        // TypeError: Cannot read property 'title' of null
    }

    buttons: [
        CpbButton {
            text: qsTr("OK")

            onClicked: {
                _storyManager.removeStory(storyToRemove)
                _popupManager.hidePopup()
            }
        },
        CpbButton {
            text: qsTr("CANCEL")

            onClicked: {
                _popupManager.hidePopup()
            }
        }
    ]
}
