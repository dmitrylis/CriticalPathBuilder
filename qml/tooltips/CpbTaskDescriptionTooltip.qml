import QtQuick 2.15

import com.cpb 1.0

import "../components"
import "../effects"
import "../singletons"

Item {
    property var task: _tooltipManager.data[0]

    QtObject {
        id: internal

        function taskTypeToString(type) {
            switch (type) {
            case Task.DevelopmentTask:
                return qsTr("Development")
            case Task.QaTask:
                return qsTr("QA")
            case Task.ResearchTask:
                return qsTr("Research")
            default:
                return qsTr("Unknown type")
            }
        }
    }

    width: body.width + _themeManager.sizes.tiny * 2
    height: body.height + _themeManager.sizes.tiny * 2

    Rectangle {
        id: body

        anchors.centerIn: parent

        width: column.width
        height: column.height
        radius: _themeManager.sizes.tiny
        color: CpbStyle.colorBlack
        layer.enabled: true
        layer.effect: CpbShadowEffect {
            alpha: 0.5
        }

        Column {
            id: column

            padding: _themeManager.sizes.small
            spacing: _themeManager.sizes.tiny

            CpbText {
                text: task ? qsTr("Title: %1").arg(task.title) : ""
                color: CpbStyle.colorWhite
            }

            CpbText {
                text: task ? qsTr("Assignee: %1").arg(task.owner) : ""
                color: CpbStyle.colorLightGrey
                visible: task ? task.owner !== "" : false
            }

            CpbText {
                text: task ? qsTr("Type: %1").arg(internal.taskTypeToString(task.type)) : ""
                color: CpbStyle.colorLightGrey
            }
        }
    }
}
