import QtQuick 2.11

import "../components"
import "../effects"
import "../singletons"

Rectangle {
    id: root

    property alias title: popupTitle.text
    property alias content: popupContentItem.children
    property alias buttons: popupButtonsRow.children

    width: 800
    height: 900
    layer.enabled: true
    layer.effect: CpbShadowEffect {
        alpha: 0.5
    }

    CpbText {
        id: popupTitle

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: CpbStyle.marginMedium
        }
    }

    Item {
        id: popupContentItem

        anchors {
            left: parent.left
            right: parent.right
            top: popupTitle.bottom
            bottom: popupButtonsItem.top
            leftMargin: CpbStyle.marginMedium
            rightMargin: CpbStyle.marginMedium
        }
    }

    Item {
        id: popupButtonsItem

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: CpbStyle.marginMedium
        }
        height: 50

        Row {
            id: popupButtonsRow

            anchors.centerIn: parent
            spacing: CpbStyle.marginTiny
        }
    }
}
