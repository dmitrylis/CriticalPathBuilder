import QtQuick 2.11
import QtQuick.Controls 2.4

Button {
    id: root

    width: 100
    height: 50

    background: Item {
        Rectangle {
            id: buttonBg

            anchors {
                fill: parent
                leftMargin: 2
                rightMargin: 2
                topMargin: 4
                bottomMargin: -buttonBg.radius
            }
            radius: 4
        }
    }

    contentItem: Text {
        id: buttonText

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: root.text
        color: "black"
        elide: Text.ElideRight
    }

    onCheckedChanged: checkable = false

    states: [
        State {
            name: "normal"
            when: !root.checked && !root.down

            PropertyChanges {
                target: buttonBg
                color: "lightgrey"
            }
        },
        State {
            name: "checked"
            when: root.checked && !root.down

            PropertyChanges {
                target: buttonBg
                color: "white"
            }
        },
        State {
            name: "normal_down"
            extend: "checked"
            when: !root.checked && root.down
        },
        State {
            name: "checked_down"
            extend: "normal"
            when: root.checked && root.down
        }
    ]
}
