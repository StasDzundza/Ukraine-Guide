import QtQuick 2.15

import "../settings"

Rectangle {
    id: header
    property string title: qsTr("Header")
    color: Palette.headerColor

    signal backClicked()

    ImageButton {
        id: backButton
        source: "qrc:/icons/go-back-icon.svg"
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 10

        onClicked: parent.backClicked()
    }

    Text {
        id: title
        text: parent.title
        anchors.centerIn: parent
        color: Palette.headerFontColor
        font.pointSize: 15
        font.bold: true
    }
}
