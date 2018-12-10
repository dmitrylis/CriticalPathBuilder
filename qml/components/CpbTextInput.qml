import QtQuick 2.11

import "../singletons"
import "../controls"

CpbBaseTextInput {
    id: root

    implicitWidth: 200
    implicitHeight: 35
    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignVCenter

    background: Item {
        CpbText {
            id: placeholder

            anchors.verticalCenter: parent.verticalCenter
            text: root.placeholderText
        }

        Rectangle {
            id: stroke

            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
        }
    }

    StateGroup {
        states: [
            State {
                name: "no_text"
                when: root.state === "no_text"

                AnchorChanges {
                    target: placeholder
                    anchors.verticalCenter: parent.verticalCenter
                }

                PropertyChanges {
                    target: placeholder
                    color: CpbStyle.darkGreyColor
                    fontSize: CpbStyle.fontMedium
                }

                PropertyChanges {
                    target: stroke
                    height: 1
                    color: CpbStyle.blueColor
                }
            },
            State {
                name: "has_text"
                when: root.state === "has_text"

                PropertyChanges {
                    target: root
                    color: CpbStyle.blackColor
                }

                AnchorChanges {
                    target: placeholder
                    anchors.verticalCenter: parent.top
                }

                PropertyChanges {
                    target: placeholder
                    color: CpbStyle.darkGreyColor
                    fontSize: CpbStyle.fontTiny
                }

                PropertyChanges {
                    target: stroke
                    height: 1
                    color: CpbStyle.blueColor
                }
            },
            State {
                name: "focused"
                when: root.state === "focused"
                extend: "has_text"

                PropertyChanges {
                    target: stroke
                    height: 2
                    color: CpbStyle.blueColor
                }
            },
            State {
                name: "no_text_disabled"
                when: root.state === "no_text_disabled"
                extend: "no_text"

                PropertyChanges {
                    target: placeholder
                    color: CpbStyle.greyColor
                }

                PropertyChanges {
                    target: stroke
                    height: 1
                    color: CpbStyle.darkGreyColor
                }
            },
            State {
                name: "has_text_disabled"
                when: root.state === "has_text_disabled"
                extend: "has_text"

                PropertyChanges {
                    target: root
                    color: CpbStyle.darkGreyColor
                }

                PropertyChanges {
                    target: placeholder
                    color: CpbStyle.greyColor
                }

                PropertyChanges {
                    target: stroke
                    height: 1
                    color: CpbStyle.darkGreyColor
                }
            }
        ]

        transitions: Transition {
            from: "no_text"
            to: "focused"
            reversible: true

            AnchorAnimation {}
            PropertyAnimation { properties: "fontSize"}
        }
    }
}
