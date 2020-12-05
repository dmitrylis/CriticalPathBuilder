import QtQuick 2.15

import com.cpb 1.0

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    width: 700
    height: 700
    title: qsTr("WELCOME")
    headerAffectsContent: false
    footerAffectsContent: false

    content: CpbParallaxView {
        id: parallaxView

        anchors.fill: parent
        backgroundPattern: "qrc:/images/bg_pattern.png"
        pageIndicatorMargin: 80

        CpbParallaxPage {
            opacity: 1.0 - Math.abs(animationProgress) // sample animation

            CpbText {
                anchors.centerIn: parent
                text: qsTr("Welcome to Critical Path Builder!")
                fontSize: CpbStyle.fontEnormous
                fontBold: true
            }
        }

        CpbParallaxPage {
            id: page2

            opacity: 1.0 - Math.abs(animationProgress) // sample animation

            Item {
                anchors.centerIn: parent
                width: 300
                height: 300

                Image {
                    anchors.centerIn: parent
                    anchors.horizontalCenterOffset: -200 * Math.abs(page2.animationProgress)

                    source: "qrc:/images/face_pic.png"
                    rotation: -50 * Math.abs(page2.animationProgress)
                }

                Image {
                    anchors.centerIn: parent
                    anchors.horizontalCenterOffset: 150
                    anchors.verticalCenterOffset: 20 + 200 * Math.abs(page2.animationProgress)
                    rotation: 20 + 50 * Math.abs(page2.animationProgress)

                    source: "qrc:/images/f_pic.png"
                }
            }
        }

        CpbParallaxPage {
            opacity: 1.0 - Math.abs(animationProgress) // sample animation

            CpbText {
                anchors.centerIn: parent
                text: qsTr("Let's go to the app!")
                fontSize: CpbStyle.fontEnormous
                fontBold: true
            }
        }
    }

    buttons: [
        CpbButton {
            text: qsTr("BACK")
            visible: parallaxView.currentIndex > 0

            onClicked: {
                parallaxView.decrementCurrentIndex()
            }
        },
        CpbButton {
            text: parallaxView.currentIndex === 2 ? qsTr("GO TO APP") : qsTr("NEXT")

            onClicked: {
                if (parallaxView.currentIndex === 2) {
                    _globalManager.setShowWelcome(false)
                    _popupManager.hide()
                }
                else {
                    parallaxView.incrementCurrentIndex()
                }
            }
        }
    ]
}
