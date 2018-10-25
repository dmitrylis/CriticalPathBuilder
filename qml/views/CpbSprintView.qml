import QtQuick 2.11

Rectangle {
    clip: true

    ListView {
        anchors.fill: parent

        model: 5 // model of stories
        delegate: CpbStoryView {
            width: ListView.view.width
        }
    }
}
