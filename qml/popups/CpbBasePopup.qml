import QtQuick 2.15

import "../components"
import "../effects"
import "../singletons"

Rectangle {
    id: root

    property alias title: titleText.text
    property alias content: contentArea.children
    property alias buttons: buttonsRow.children
    property alias closeButtonVisible: closeButton.visible
    property bool headerAffectsContent: true
    property bool footerAffectsContent: true

    QtObject {
        id: internal

        function buttonWidth(count) {
            switch (count) {
            case 1: return 240 + CpbStyle.marginTiny
            case 2: return 120
            case 3:
            default: return 100
            }
        }

        function updateButtonsWidth() {
            const buttonWidth = internal.buttonWidth(buttonsRow.visibleChildren.length)
            for (var i = 0; i < buttonsRow.visibleChildren.length; ++i) {
                buttonsRow.visibleChildren[i].width = buttonWidth
            }
        }
    }

    width: 400
    height: 300
    layer.enabled: true
    layer.effect: CpbShadowEffect {
        alpha: 0.5
    }

    Component.onCompleted: {
        internal.updateButtonsWidth()
    }

    Item {
        id: contentArea

        anchors {
            fill: parent
            topMargin: root.headerAffectsContent ? titleArea.height : 0
            bottomMargin: root.footerAffectsContent ? buttonsArea.height : 0
        }
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
            fontSize: CpbStyle.fontHuge
            fontBold: true
        }
    }

    CpbRemoveButton {
        id: closeButton

        anchors {
            right: parent.right
            top: parent.top
            margins: CpbStyle.marginSmall
        }
        visible: false

        onClicked: {
            _popupManager.hide()
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

            onVisibleChildrenChanged: {
                internal.updateButtonsWidth()
            }
        }
    }
}
