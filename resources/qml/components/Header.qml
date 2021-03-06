import QtQuick 2.15

import "../settings"

Rectangle {
    id: header
    property string title: qsTr("Header")
    property alias titleColor: title.color
    color: Palette.headerColor

    signal backClicked()
    signal starClicked()
    signal titleTriggered()

    ImageButton {
        id: backButton
        source: "qrc:/icons/arrow-back.svg"
        anchors.verticalCenter: parent.verticalCenter
        x: 10 // left margin

        onClicked: parent.backClicked()
    }

    Text {
        id: title
        text: parent.title
        anchors.centerIn: parent
        color: Palette.headerTextColor
        font.pointSize: AppSettings.titleFontSize
        font.bold: true

        MouseArea {
            anchors.fill: parent
            onClicked: header.titleTriggered()
        }
    }
}
