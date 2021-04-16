pragma Singleton
import QtQuick 2.15

QtObject {
    // page url's
    readonly property string homePageUrl: "qrc:/qml/pages/HomePage.qml"
    readonly property string aboutPageUrl: "qrc:/qml/pages/AboutPage.qml"
    readonly property string localityListPageUrl: "qrc:/qml/pages/LocalityListPage.qml"
    readonly property string localityDescriptionPageUrl: "qrc:/qml/pages/LocalityDescriptionPage.qml"
    readonly property string mapViewPageUrl: "qrc:/qml/pages/MapViewPage.qml"
}
