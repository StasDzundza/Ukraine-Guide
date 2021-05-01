pragma Singleton
import QtQuick 2.15

QtObject {
    // page url's
    readonly property string homePageUrl: "qrc:/qml/pages/HomePage.qml"
    readonly property string aboutPageUrl: "qrc:/qml/pages/AboutPage.qml"
    readonly property string localityListPageUrl: "qrc:/qml/pages/LocalityListPage.qml"
    readonly property string localityDescriptionPageUrl: "qrc:/qml/pages/LocalityDescriptionPage.qml"
    readonly property string mapViewPageUrl: "qrc:/qml/pages/MapViewPage.qml"
    readonly property string establishmentsListPage: "qrc:/qml/pages/EstablishmentsListPage.qml"
    readonly property string routesListPageUrl: "qrc:/qml/pages/RouteListPage.qml"
    readonly property string routePageUrl: "qrc:/qml/pages/RoutePage.qml"
    readonly property string creatingRoutePageUrl: "qrc:/qml/pages/CreatingRoutePage.qml"
    readonly property string addLocalityToRoutePageUrl: "qrc:/qml/pages/AddLocalityToRoutePage.qml"
}
