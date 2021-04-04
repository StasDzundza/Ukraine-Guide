import QtQuick 2.15
import QtQuick.Controls 2.15

import "./settings"

ApplicationWindow {
    id: window
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    visible: true
    title: qsTr("Ukraine Guide")

    StackView {
        id: stackView
        initialItem: "qrc:/qml/pages/HomePage.qml"
        anchors.fill: parent
    }
}
