import QtQuick 2.15
import QtQuick.Controls 2.15

import "../settings"
import "../components"

Page {
    width: parent.width
    height: parent.height
    title: qsTr("About")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        Header {
            width: parent.width
            height: 50
            title: qsTr("About")

            onBackClicked: pageStack.pop()
        }

        Text {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Ukraine Guide mobile application.\nDiploma work of Stanislav Dzundza")
            color: Palette.blockTextColor
            font.pointSize: AppSettings.blockTextFontSize
        }
    }
}
