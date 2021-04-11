import QtQuick 2.15
import QtQuick.Controls 2.15

import "./settings"
import "./pages"

ApplicationWindow {
    id: window
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    visible: true
    title: qsTr("Ukraine Guide")

    StackView {
        id: pageStack
        initialItem: Pages.homePageUrl
        anchors.fill: parent

        Keys.onBackPressed: {
            if (pageStack.empty) {
                exitConfirmationPopup.open()
            }
        }
    }

    Popup {
        id: exitConfirmationPopup
        anchors.centerIn: parent
        width: parent.width / 2
        height: width
    }
}
