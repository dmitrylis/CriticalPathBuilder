import QtQuick 2.11

import "../singletons"

Text {
    id: root

    property int fontSize: CpbStyle.fontMedium

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    color: CpbStyle.blackColor
    font.pixelSize: root.fontSize
    elide: Text.ElideRight
}
