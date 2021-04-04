import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4

import "../settings"

Page {
    width: parent.width
    height: parent.height
    title: qsTr("Home")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        Button {
            anchors.centerIn: parent
            width: parent.width / 2
            height: 40
            text: qsTr("About")

            onClicked: pageStack.push(Pages.aboutPageUrl)
        }
    }
}
