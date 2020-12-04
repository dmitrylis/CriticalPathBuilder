import QtQuick 2.15

import com.cpb 1.0

import "../singletons"
import "../components"

CpbBasePopup {
    id: root

    width: 700
    height: 700

    content: CpbParallaxView {
        id: parallaxView

        anchors.fill: parent
        backgroundPattern: "qrc:/images/bg_pattern.png"

        CpbParallaxPage {
            opacity: 1.0 - Math.abs(animationProgress) // sample animation

            Column {
                anchors.centerIn: parent
                spacing: CpbStyle.marginHuge

                CpbText {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Welcome to Critical Path Builder!")
                    fontSize: CpbStyle.fontEnormous
                    fontBold: true
                }

                CpbButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("NEXT")

                    onClicked: {
                        parallaxView.incrementCurrentIndex()
                    }
                }
            }
        }

        CpbParallaxPage {
            id: page2

            opacity: 1.0 - Math.abs(animationProgress) // sample animation

            Column {
                anchors.centerIn: parent
                spacing: CpbStyle.marginHuge

                CpbText {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("TBD")
                    fontSize: CpbStyle.fontEnormous
                    fontBold: true
                }

                Item {
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

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: CpbStyle.marginHuge

                    CpbButton {
                        text: qsTr("BACK")

                        onClicked: {
                            parallaxView.decrementCurrentIndex()
                        }
                    }

                    CpbButton {
                        text: qsTr("NEXT")

                        onClicked: {
                            parallaxView.incrementCurrentIndex()
                        }
                    }
                }
            }
        }

        CpbParallaxPage {
            opacity: 1.0 - Math.abs(animationProgress) // sample animation

            Column {
                anchors.centerIn: parent
                spacing: CpbStyle.marginHuge

                CpbText {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Let's go to the app!")
                    fontSize: CpbStyle.fontEnormous
                    fontBold: true
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: CpbStyle.marginHuge

                    CpbButton {
                        text: qsTr("BACK")

                        onClicked: {
                            parallaxView.decrementCurrentIndex()
                        }
                    }

                    CpbButton {
                        text: qsTr("GO TO APP")

                        onClicked: {
                            _globalManager.setShowWelcome(false)
                            _popupManager.hide()
                        }
                    }
                }
            }
        }
    }

}
