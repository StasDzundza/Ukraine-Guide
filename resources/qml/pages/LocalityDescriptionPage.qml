import QtQuick 2.15
import QtQuick.Controls 2.15

import "../settings"
import "../components"

Page {
    property var localityModel // : app.getCurModel
    width: parent !== null ? parent.width : 0
    height: parent !== null ? parent.height : 0
    title: qsTr("Locality list")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        Header {
            width: parent.width
            height: 50
            title: ""// model.ukrName

            onBackClicked: pageStack.pop()
        }
    }
}
