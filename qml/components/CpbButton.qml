import QtQuick 2.11

import "../controls"
import "../singletons"

CpbBaseButton {
    id: root

    implicitWidth: 100
    implicitHeight: 50

    background: Rectangle {
        id: buttonBg

        radius: CpbStyle.marginTiny
    }

    contentItem: CpbText {
        leftPadding: CpbStyle.marginSmall
        rightPadding: CpbStyle.marginSmall
        text: root.text
    }

    StateGroup {
        states: [
            State {
                name: "normal"
                when: root.state === "normal"

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.greyColor
                }
            },
            State {
                name: "normal_hovered"
                when: root.state === "normal_hovered"

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.lightGreyColor
                }
            },
            State {
                name: "normal_down"
                when: root.state === "normal_down"

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.whiteColor
                }
            }
        ]
    }
}
