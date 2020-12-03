import QtQuick 2.15

import "../controls"
import "../singletons"

CpbBaseButton {
    id: root

    implicitWidth: CpbStyle.cellWidth
    implicitHeight: CpbStyle.cellHeight

    background: Image {
        id: buttonBg

        source: "qrc:/images/add_task.png"
    }

    StateGroup {
        states: [
            State {
                name: "normal"
                when: root.state === "normal"

                PropertyChanges {
                    target: buttonBg
                    opacity: 0.3
                }
            },
            State {
                name: "normal_hovered"
                when: root.state === "normal_hovered"

                PropertyChanges {
                    target: buttonBg
                    opacity: 1.0
                }
            },
            State {
                name: "normal_down"
                when: root.state === "normal_down"

                PropertyChanges {
                    target: buttonBg
                    opacity: 0.6
                }
            }
        ]
    }
}
