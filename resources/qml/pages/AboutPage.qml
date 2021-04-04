import QtQuick 2.15
import QtQuick.Controls 2.15

import "../settings"
import "../components"

Page {
    width: parent.width
    height: parent.height

    title: qsTr("About")

    Header {
        width: parent.width
        height: 50
        title: qsTr("About")

        onBackClicked: pageStack.push(AppSettings.homePageUrl)
    }

    Text {
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        text: qsTr("Ukraine Guide mobile application.\nDiploma work of Stanislav Dzundza")
        color: Palette.textBlockColor
        font.pointSize: 12
    }
}
