import QtQuick 2.15

Flickable {
    id: root

    property alias model: repeater.model
    property alias expandedSpacing: row.spacing
    property int collapsedSpacing: expandedSpacing
    property alias delegate: repeater.delegate

    contentWidth: row.width

    Row {
        id: row

        Repeater {
            id: repeater

            onItemAdded:  {
                if (item === null) return

                item.x = Qt.binding(function () {
                    var originX = index * (item.width + root.expandedSpacing)
                    var offset = root.contentX - root.originX + index * root.collapsedSpacing
                    return Math.max(offset, originX)
                })
            }
        }
    }
}

