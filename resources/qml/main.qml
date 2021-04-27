import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.15

import "./settings"
import "./pages"
import "./components"

ApplicationWindow {
    id: window
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    visible: true
    title: qsTr("Ukraine Guide")

    Material.accent: Material.Lime
    Material.background: Material.Lime
    Material.foreground: Material.Cyan
    Material.primary: Material.Cyan

    StackView {
        id: pageStack
        initialItem: Pages.homePageUrl
        anchors.fill: parent

        Keys.onBackPressed: pop()
    }
}
