import QtQuick 2.11

import "../controls"
import "../singletons"
import "../effects"

Item {
    id: root

    property alias model: daysRepeater.model

    width: daysBg.width + CpbStyle.marginMedium
    height: daysBg.height + CpbStyle.marginMedium

    Rectangle {
        id: daysBg

        anchors.centerIn: parent
        width: daysRow.width
        height: daysRow.height
        color: CpbStyle.lightGreyColor
        radius: CpbStyle.marginTiny

        layer.enabled: true
        layer.effect: CpbShadowEffect {
            alpha: 0.5
        }

        Row {
            id: daysRow

            Repeater {
                id: daysRepeater

                delegate: Item {
                    width: CpbStyle.cellWidth
                    height: CpbStyle.cellHeight

                    Column {
                        anchors.centerIn: parent
                        width: parent.width
                        spacing: CpbStyle.marginTiny

                        CpbText {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.width
                            text: dayNameRole
                        }

                        CpbText {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.width
                            text: dayNumberRole
                            fontSize: CpbStyle.fontLarge
                            fontBold: true
                            color: holidayRole ? "red" : CpbStyle.blackColor
                        }

                        CpbText {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.width
                            text: monthNameRole
                            color: CpbStyle.darkGreyColor
                        }
                    }
                }
            }
        }
    }
}
