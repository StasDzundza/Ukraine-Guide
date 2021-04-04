pragma Singleton
import QtQuick 2.15
import QtQuick.Window 2.15

QtObject {
    property real screenWidth: Screen.width
    property real screenHeight: Screen.height

    // page url's
    property string homePageUrl: "qrc:/qml/pages/HomePage.qml"
    property string aboutPageUrl: "qrc:/qml/pages/AboutPage.qml"
}
