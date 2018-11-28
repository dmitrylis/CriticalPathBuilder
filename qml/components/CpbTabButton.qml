import QtQuick 2.11
import QtQuick.Templates 2.4

import "../controls"
import "../singletons"

CpbBaseButton {
    id: root

    signal removeClicked()

    width: 100
    height: 50

    background: Item {
        Rectangle {
            id: buttonBg

            anchors {
                fill: parent
                bottomMargin: -buttonBg.radius
            }
            radius: CpbStyle.marginTiny
        }
    }

    contentItem: Item {
        CpbText {
            anchors {
                left: parent.left
                right: removeButton.left
                verticalCenter: parent.verticalCenter
            }
            horizontalAlignment: Text.AlignLeft
            leftPadding: CpbStyle.marginSmall
            rightPadding: CpbStyle.marginSmall
            text: root.text
        }

        CpbRemoveButton {
            id: removeButton

            anchors {
                right: parent.right
                rightMargin: CpbStyle.marginTiny
                verticalCenter: parent.verticalCenter
            }

            onClicked: {
                root.removeClicked()
            }
        }
    }

    onCheckedChanged: checkable = false

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
            },
            State {
                name: "checked"
                extend: "normal_down"
                when: root.state === "checked"
            },
            State {
                name: "checked_hovered"
                extend: "normal_hovered"
                when: root.state === "checked_hovered"
            },
            State {
                name: "checked_down"
                extend: "normal"
                when: root.state === "checked_down"
            }
        ]
    }
}
