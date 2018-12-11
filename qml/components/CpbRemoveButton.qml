import QtQuick 2.11

import "../controls"
import "../singletons"

CpbBaseButton {
    id: root

    implicitWidth: 25
    implicitHeight: 25

    background: Rectangle {
        id: buttonBg

        radius: root.height / 2
    }

    contentItem: Image {
        source: "qrc:/images/remove_icon_tiny.png"
    }

    StateGroup {
        states: [
            State {
                name: "normal"
                when: root.state === "normal"

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.colorLightGrey
                }
            },
            State {
                name: "normal_hovered"
                when: root.state === "normal_hovered"

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.colorGrey
                }
            },
            State {
                name: "normal_down"
                when: root.state === "normal_down"

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.colorDarkGrey
                }
            }
        ]
    }
}
