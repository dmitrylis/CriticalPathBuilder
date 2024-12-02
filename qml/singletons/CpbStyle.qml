pragma Singleton
import QtQuick 2.15

Item {
    // font sizes section
    readonly property int fontTiny: 8
    readonly property int fontSmall: 10
    readonly property int fontMedium: 12
    readonly property int fontLarge: 14
    readonly property int fontHuge: 16
    readonly property int fontGiant: 18
    readonly property int fontEnormous: 20

    // colors section
    readonly property color colorTransparent: "#00FFFFFF"
    readonly property color colorWhite: "#FFFFFF"
    readonly property color colorBlack: "#000000"
    readonly property color colorLightGrey: "#F5F5F5"
    readonly property color colorGrey: "#BEBEBE"

    readonly property color colorDarkGrey: "#808080" // foreground??

    readonly property color colorGreen: "#67ab49" // color from Jira
    readonly property color colorBlue: "#3b7fc4" // color from Jira
    readonly property color colorOrange: "#ff9933" // color from Jira
    readonly property color colorCyan: "#009aa2"
}
