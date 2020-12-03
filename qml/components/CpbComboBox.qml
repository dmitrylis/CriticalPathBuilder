import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.12

import "../controls"
import "../effects"
import "../singletons"

CpbBaseComboBox {
    id: root

    implicitWidth: 200
    implicitHeight: 35

    delegate: ItemDelegate {
        width: root.width
        height: root.height
        highlighted: root.highlightedIndex === index

        contentItem: CpbText {
            horizontalAlignment: Text.AlignLeft
            text: root.textRole ? (Array.isArray(root.model) ? modelData[root.textRole] : model[root.textRole]) : modelData
        }
    }

    indicator: Item {
        anchors.right: parent.right
        width: root.height
        height: root.height

        Image {
            id: comboArrow

            anchors.centerIn: parent
            source: "qrc:/images/combo_arrow.png"
            Behavior on rotation { NumberAnimation { duration: 250 } }
        }
    }

    contentItem: CpbText {
        id: mainText

        horizontalAlignment: Text.AlignLeft
        text: root.displayText
    }

    background: Item {
        CpbText {
            id: placeholder

            anchors.verticalCenter: parent.top
            color: CpbStyle.colorDarkGrey
            scale: 0.8
            text: root.placeholderText
            transformOrigin: Item.Left
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

    popup: Popup {
        id: popupItem

        property int dynamicRadius: y !== root.height ? CpbStyle.marginTiny : 0
        property var radius: [dynamicRadius, dynamicRadius, CpbStyle.marginTiny, CpbStyle.marginTiny]

        y: root.height
        width: root.width
        implicitHeight: contentItem.implicitHeight
        padding: 0

        contentItem: ListView {
            id: view

            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: CpbRectangle {
                    width: view.width
                    height: view.height
                    radius: popupItem.radius
                }
            }

            implicitHeight: contentHeight
            model: root.delegateModel
            currentIndex: root.highlightedIndex
            highlightMoveDuration: 0

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: CpbRectangle {
            radius: popupItem.radius
            layer.enabled: true
            layer.effect: CpbShadowEffect {
                alpha: 0.5
            }
        }
    }

    StateGroup {
        states: [
            State {
                name: "normal"
                when: root.state === "normal"

                PropertyChanges {
                    target: stroke
                    height: 1
                    color: CpbStyle.colorBlue
                }
            },
            State {
                name: "focused"
                when: root.state === "focused"

                PropertyChanges {
                    target: stroke
                    height: 2
                    color: CpbStyle.colorBlue
                }
            },
            State {
                name: "focused_pressed"
                when: root.state === "focused_pressed"

                PropertyChanges {
                    target: stroke
                    height: 2
                    color: CpbStyle.colorBlue
                }

                PropertyChanges {
                    target: comboArrow
                    opacity: 0.5
                }
            },
            State {
                name: "expanded"
                when: root.state === "expanded"

                PropertyChanges {
                    target: stroke
                    height: 2
                    color: CpbStyle.colorBlue
                }

                PropertyChanges {
                    target: comboArrow
                    rotation: 180
                }
            },
            State {
                name: "expanded_pressed"
                when: root.state === "expanded_pressed"

                PropertyChanges {
                    target: stroke
                    height: 2
                    color: CpbStyle.colorBlue
                }

                PropertyChanges {
                    target: comboArrow
                    rotation: 180
                    opacity: 0.5
                }
            },
            State {
                name: "disabled"
                when: root.state === "disabled"

                PropertyChanges {
                    target: stroke
                    height: 1
                    color: CpbStyle.colorDarkGrey
                }

                PropertyChanges {
                    target: comboArrow
                    opacity: 0.3
                }
            }
        ]
    }
}
