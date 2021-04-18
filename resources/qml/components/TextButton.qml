import QtQuick 2.15

import "../settings"

Text {
    font.bold: true
    font.pointSize: AppSettings.titleFontSize
    color: Palette.blockTextColor

    signal clicked()

    MouseArea {
        anchors.fill: parent

        onClicked: parent.clicked()
    }
}
