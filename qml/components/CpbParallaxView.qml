import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    default property alias content: visualModel.children
    property alias backgroundPattern: background.source
    property alias currentIndex: listView.currentIndex
    property int pageIndicatorMargin: 0

    function incrementCurrentIndex() {
        listView.incrementCurrentIndex()
    }

    function decrementCurrentIndex() {
        listView.decrementCurrentIndex()
    }

    QtObject {
        id: internal

        property real percentage: (listView.originX - listView.contentX) / (listView.contentWidth - root.width)
    }

    clip: true

    Image {
        id: background

        x: Math.max(-1.0, Math.min(internal.percentage, 0.0)) * (width - root.width)
        height: parent.height
        width: 1.25 * parent.width
        fillMode: Image.Tile
    }

    ListView {
        id: listView

        anchors.fill: parent
        orientation: Qt.Horizontal
        boundsBehavior: Flickable.DragOverBounds
        model: ObjectModel { id: visualModel }
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 500
        snapMode: ListView.SnapOneItem
    }

    PageIndicator {
        anchors {
            bottom: listView.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin: root.pageIndicatorMargin
        }
        count: listView.count
        currentIndex: listView.currentIndex
    }
}
