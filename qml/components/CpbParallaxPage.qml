import QtQuick 2.15
import QtQml.Models 2.15

import "../singletons"
import "../effects"

Item {
    id: root

    readonly property ListView view: ListView.view
    readonly property int index: ObjectModel.index
    readonly property real animationProgress: ((view.contentX - view.originX) / view.width) - root.index

    width: view.width
    height: view.height
}
