import QtQuick 2.15

import "../singletons"

Text {
    id: root

    property int fontSize: CpbStyle.fontMedium
    property bool fontBold: false

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    color: CpbStyle.colorBlack
    elide: Text.ElideRight

    font {
        pixelSize: root.fontSize
        bold: root.fontBold
    }
}
