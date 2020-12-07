import QtQuick 2.15

import QtQuick.Controls 2.15

import "../components"
import "../singletons"

CpbBasePopup {
    id: root

    width: 700
    height: 700
    title: qsTr("Settings")
    closeButtonVisible: true

    content: Item {
        anchors.fill: parent

        Item {
            id: tabMenuArea

            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
            }
            width: parent.width * 0.3

            Column {
                anchors {
                    fill: parent
                    margins: CpbStyle.marginSmall
                }
                spacing: CpbStyle.marginSmall

                CpbButton {
                    width: parent.width
                    text: qsTr("Preferences")

                    onClicked: {
                        if (contentView.currentItem.pageId !== 0) {
                            contentView.replace(preferencesPage)
                        }
                    }
                }

                CpbButton {
                    width: parent.width
                    text: qsTr("Users")

                    onClicked: {
                        if (contentView.currentItem.pageId !== 1) {
                            contentView.replace(usersPage)
                        }
                    }
                }

                CpbButton {
                    width: parent.width
                    text: qsTr("About")

                    onClicked: {
                        if (contentView.currentItem.pageId !== 2) {
                            contentView.replace(aboutPage)
                        }
                    }
                }
            }
        }

        Item { // menu content
            anchors {
                left: tabMenuArea.right
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            StackView {
                id: contentView

                anchors.fill: parent
                initialItem: preferencesPage
                clip: true
            }

            Component {
                id: preferencesPage

                Column {
                    property int pageId: 0

                    spacing: CpbStyle.marginSmall

                    Switch {
                        width: parent.width
                        text: qsTr("Theme: %1").arg(checked ? "Light" : "Dark")
                    }

                    CpbButton {
                        width: parent.width
                        text: "show welcome"

                        onClicked: _globalManager.setShowWelcome(true)
                    }
                }
            }

            Component {
                id: usersPage

                Item {
                    property int pageId: 1

                    ListView {
                        anchors.fill: parent
                        model: _userManager.userModel
                        delegate: Item {
                            width: parent.width
                            height: 40

                            Text {
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                    leftMargin: 20
                                }
                                text: nameRole
                            }
                        }
                    }
                }
            }

            Component {
                id: aboutPage

                Item {
                    property int pageId: 2

                    Image {
                        anchors.centerIn: parent
                        source: "qrc:/images/digital_mankind_logo.png"
                    }
                }
            }
        }
    }
}
