import QtQuick 2.15
import QtQuick.Controls 2.15

import "../settings"
import "../components"

Page {
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("About")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        Header {
            width: parent.width
            height: AppSettings.headerHeight
            title: qsTr("Про нас")

            onBackClicked: pageStack.pop()
        }

        Text {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Ukraine Guide - мобільний додаток для комфортних подорожей\nУкраїною.\nДипломна робота Дзундзи Станіслава Васильовича")
            color: Palette.blockTextColor
            font.pointSize: AppSettings.blockTextFontSize
        }
    }
}
