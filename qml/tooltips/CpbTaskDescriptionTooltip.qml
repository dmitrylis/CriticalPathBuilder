import QtQuick 2.11

import "../components"
import "../effects"
import "../singletons"

Item {
    property var task: _tooltipManager.data[0]

    width: body.width + CpbStyle.marginTiny * 2
    height: body.height + CpbStyle.marginTiny * 2

    Rectangle {
        id: body

        anchors.centerIn: parent

        width: column.width
        height: 50
        radius: CpbStyle.marginTiny
        color: CpbStyle.colorBlack
        layer.enabled: true
        layer.effect: CpbShadowEffect {
            alpha: 0.5
        }

        Column {
            id: column

            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            padding: CpbStyle.marginSmall
            spacing: CpbStyle.marginTiny

            CpbText {
                horizontalAlignment: Text.AlignLeft
                text: task ? task.title : ""
                color: CpbStyle.colorWhite
            }

            CpbText {
                horizontalAlignment: Text.AlignLeft
                text: task ? task.owner : ""
                color: CpbStyle.colorLightGrey
                visible: text !== ""
            }
        }
    }
}
