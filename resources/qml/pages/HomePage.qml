import QtQuick 2.15
import QtQuick.Controls 2.15

import "../settings"

Page {
    width: parent.width
    height: parent.height

    title: qsTr("Home")

    Rectangle {
        anchors.centerIn: parent
        width: parent.width / 2
        height: parent.height / 6
        color: Palette.headerColor
    }
}
