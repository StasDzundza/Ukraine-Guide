pragma Singleton
import QtQuick 2.15
import QtQuick.Window 2.15

QtObject {
    property real screenWidth: Screen.width
    property real screenHeight: Screen.height

    // font sizes
    property int blockTextFontSize: 13
    property int titleFontSize: 18
    property int buttonTextFontSize: 15
}
