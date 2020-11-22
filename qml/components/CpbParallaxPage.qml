import QtQuick 2.12
import QtQml.Models 2.15

import "../singletons"
import "../effects"

Item {
    id: root

    default property alias content: contentRect.children
    readonly property ListView view: ListView.view
    readonly property int index: ObjectModel.index
    readonly property real animationProgress: (view.contentX / view.width) - root.index

    width: view.width
    height: view.height

    Rectangle {
        id: contentRect

        anchors {
            fill: parent
            margins: CpbStyle.marginEnormous
        }
        radius: CpbStyle.marginSmall
        opacity: 0.8
        layer.enabled: true
        layer.effect: CpbShadowEffect {
            alpha: 0.5
        }
    }
}
