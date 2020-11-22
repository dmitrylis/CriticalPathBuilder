import QtQuick 2.11
import QtQuick.Controls 2.5

import "../components"
import "../singletons"
import "../effects"

Rectangle {
    id: root

    CpbParallaxView {
        id: parallaxView

        anchors.fill: parent
        backgroundPattern: "qrc:/images/bg_pattern.png"

        Item {
            width: root.width
            height: root.height

            Rectangle {
                anchors {
                    fill: parent
                    margins: CpbStyle.marginEnormous
                }
                radius: CpbStyle.marginSmall
                opacity: 0.8
                layer.enabled: true
                layer.effect: CpbShadowEffect {
                    alpha: 0.5
                }

                CpbButton {
                    anchors.centerIn: parent
                    text: "NEXT"

                    onClicked: {
                        parallaxView.incrementCurrentIndex()
                    }
                }
            }
        }

        Item {
            width: root.width
            height: root.height

            Rectangle {
                anchors {
                    fill: parent
                    margins: CpbStyle.marginEnormous
                }
                radius: CpbStyle.marginSmall
                opacity: 0.8
                layer.enabled: true
                layer.effect: CpbShadowEffect {
                    alpha: 0.5
                }

                CpbButton {
                    anchors.centerIn: parent
                    text: "NEXT"

                    onClicked: {
                        parallaxView.incrementCurrentIndex()
                    }
                }
            }
        }

        Item {
            width: root.width
            height: root.height

            Rectangle {
                anchors {
                    fill: parent
                    margins: CpbStyle.marginEnormous
                }
                radius: CpbStyle.marginSmall
                opacity: 0.8
                layer.enabled: true
                layer.effect: CpbShadowEffect {
                    alpha: 0.5
                }
            }

            CpbButton {
                anchors.centerIn: parent
                text: "GO TO APP"

                onClicked: {
                    _globalManager.finishWelcome()
                }
            }
        }
    }
}
