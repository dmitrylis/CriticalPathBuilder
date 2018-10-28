import QtQuick 2.11

Rectangle {
    clip: true

    ListView {
        id: visualModel
        anchors.fill: parent

        model: 5 // model of stories
        delegate: CpbStoryView {
            id: icon

            width: ListView.view.width

            MouseArea {
                property int visualIndex: visualModel.count

                anchors.fill: parent
                drag.target: parent
                drag.axis: Drag.YAxis

                DropArea {
                    anchors {
                        fill: parent
                        margins: 15
                    }

                    onEntered: visualModel.items.move(drag.source.visualIndex, icon.visualIndex)
                }
            }
        }
    }
}
