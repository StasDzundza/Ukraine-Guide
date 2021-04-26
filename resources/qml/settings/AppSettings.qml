pragma Singleton
import QtQuick 2.15
import QtQuick.Window 2.15

QtObject {
    readonly property real screenWidth: Screen.width
    readonly property real screenHeight: Screen.height

    // font sizes
    readonly property int blockTextFontSize: 13
    readonly property int titleFontSize: 18
    readonly property int buttonTextFontSize: 15
    readonly property int descriptionHeaderFontSize: 20
    readonly property int placeholderFontSize: 10

    // component sizes
    readonly property int headerHeight: 50
}
