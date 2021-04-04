import QtQuick 2.15
import QtQuick.Controls 2.15

import "../settings"

Page {
    width: parent.width
    height: parent.height

    title: qsTr("Home")

    Button {
        anchors.centerIn: parent
        width: parent.width / 2
        height: 40
        text: qsTr("About")

        onClicked: pageStack.push(AppSettings.aboutPageUrl)
    }
}
