pragma Singleton
import QtQuick 2.15

QtObject {
    property string currentPageUrl: ""
    property string prevPageUrl: ""

    // page url's
    readonly property string homePageUrl: "qrc:/qml/pages/HomePage.qml"
    readonly property string aboutPageUrl: "qrc:/qml/pages/AboutPage.qml"
}
