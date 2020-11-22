import QtQuick 2.11

import "../components"

Rectangle {
    id: root

    CpbParallaxView {
        id: parallaxView

        anchors.fill: parent
        backgroundPattern: "qrc:/images/bg_pattern.png"

        CpbParallaxPage {
            id: page1

            CpbButton {
                anchors.centerIn: parent
                text: "NEXT"

                onClicked: {
                    parallaxView.incrementCurrentIndex()
                }
            }
        }

        CpbParallaxPage {
            CpbButton {
                anchors.centerIn: parent
                text: "NEXT"

                onClicked: {
                    parallaxView.incrementCurrentIndex()
                }
            }
        }

        CpbParallaxPage {
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
