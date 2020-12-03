import QtQuick 2.15

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
        id: buttonContent

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
                    color: CpbStyle.colorGrey
                }
            },
            State {
                name: "normal_hovered"
                when: root.state === "normal_hovered"

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.colorLightGrey
                }
            },
            State {
                name: "normal_down"
                when: root.state === "normal_down"

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.colorWhite
                }
            },
            State {
                name: "normal_disabled"
                when: root.state === "normal_disabled"

                PropertyChanges {
                    target: buttonContent
                    color: CpbStyle.colorGrey
                }

                PropertyChanges {
                    target: buttonBg
                    color: CpbStyle.colorLightGrey
                }
            }
        ]

        transitions: Transition {
            from: "normal, normal_hovered, normal_down, normal_disabled"
            to: "normal, normal_hovered, normal_down, normal_disabled"

            ColorAnimation { duration: 130 }
        }
    }
}
