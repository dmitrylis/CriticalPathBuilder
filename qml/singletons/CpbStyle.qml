pragma Singleton
import QtQuick 2.11

Item {
    // margins section
    readonly property int marginTiny: 5
    readonly property int marginSmall: 10
    readonly property int marginMedium: 15
    readonly property int marginLarge: 20
    readonly property int marginHuge: 25

    // font sizes section
    readonly property int fontTiny: 8
    readonly property int fontSmall: 10
    readonly property int fontMedium: 12
    readonly property int fontLarge: 14
    readonly property int fontHuge: 16

    // colors section
    readonly property color whiteColor: "#FFFFFF"
    readonly property color blackColor: "#000000"
    readonly property color lightGreyColor: "#F5F5F5"
    readonly property color greyColor: "#BEBEBE"
    readonly property color darkGreyColor: "#808080"
    readonly property color greenColor: "green"
}
