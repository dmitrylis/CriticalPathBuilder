import QtQuick 2.15

import "../components"
import "../effects"
import "../singletons"

Rectangle {
    id: root

    property alias title: titleText.text
    property alias content: contentArea.children
    property alias buttons: buttonsRow.children

    width: 400
    height: 300
    layer.enabled: true
    layer.effect: CpbShadowEffect {
        alpha: 0.5
    }

    Item {
        id: titleArea

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: !!titleText.text ? 50 : 0

        CpbText {
            id: titleText

            anchors.fill: parent
        }
    }

    Item {
        id: contentArea

        anchors {
            left: parent.left
            right: parent.right
            top: titleArea.bottom
            bottom: buttonsArea.top
        }
    }

    Item {
        id: buttonsArea

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: buttonsRow.visibleChildren.length > 0 ? 80 : 0

        Row {
            id: buttonsRow

            anchors.centerIn: parent
            spacing: CpbStyle.marginTiny
        }
    }
}
