import QtQuick 2.15

import "../settings"

Rectangle {
    property alias text: buttonText.text
    color: Palette.acceptButtonColor
    radius: 5
    border.width: 2
    border.color: Palette.borderColor

    signal clicked()

    Text {
        id: buttonText
        anchors.centerIn: parent
        color: Palette.buttoTextColor
        font.pointSize: AppSettings.buttonTextFontSize
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}

