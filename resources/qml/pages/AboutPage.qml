import QtQuick 2.15
import QtQuick.Controls 2.15

import "../settings"

Page {
    width: parent.width
    height: parent.height

    title: qsTr("About")

    Label {
        text: qsTr("About Ukraine Guide.")
        anchors.centerIn: parent
    }
}
