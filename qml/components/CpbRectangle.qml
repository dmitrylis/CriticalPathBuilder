// Example
//
// CpbRectangle {
//     anchors {
//         fill: parent
//         margins: 100
//     }
//     radius: [10, 30, 60, 100]
// }

import QtQuick 2.11

Item {
    id: root

    property color color: "white"
    property var radius: [0, 0, 0, 0] // [lt, rt, rb, lb] or number

    QtObject {
        id: internal

        property int maxRadius: Math.min(root.width / 2, root.height / 2)

        function drawRectangle(context) {
            var input = root.radius
            var output = [0, 0, 0, 0]
            var width = root.width
            var height = root.height

            if (typeof input === 'number') {
                output = [input, input, input, input]
            }
            else if (Array.isArray(input) && input.length === 4) {
                for (var index in output) {
                    output[index] = Math.max(0, Math.min(input[index], internal.maxRadius))
                }
            }
            else {
                console.warn("radius is incorrect", input)
            }

            context.beginPath()
            context.moveTo(output[0], 0)
            context.lineTo(width - output[1], 0)
            context.quadraticCurveTo(width, 0, width, output[1])
            context.lineTo(width, height - output[2])
            context.quadraticCurveTo(width, height, width - output[2], height)
            context.lineTo(output[3], height)
            context.quadraticCurveTo(0, height, 0, height - output[3])
            context.lineTo(0, output[0])
            context.quadraticCurveTo(0, 0, output[0], 0)
            context.closePath()

            context.fillStyle = root.color
            context.fill()
        }
    }

    onRadiusChanged: canvas.requestPaint()

    Canvas {
        id: canvas

        anchors.fill: parent

        onPaint: internal.drawRectangle(getContext("2d"))
    }
}
