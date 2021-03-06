pragma Singleton
import QtQuick 2.15

Item {
    // margins section
    readonly property int marginTiny: 5
    readonly property int marginSmall: 10
    readonly property int marginMedium: 15
    readonly property int marginLarge: 20
    readonly property int marginHuge: 25
    readonly property int marginGiant: 30
    readonly property int marginEnormous: 35

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
    readonly property color colorDarkGrey: "#808080"
    readonly property color colorGreen: "#67ab49" // color from Jira
    readonly property color colorBlue: "#3b7fc4" // color from Jira
    readonly property color colorOrange: "#ff9933" // color from Jira
    readonly property color colorCyan: "#009aa2"

    // grid
    readonly property int cellWidth: 70
    readonly property int cellHeight: 70
}
