import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4

import "../settings"
import "../components"

Page {
    width: parent.width
    height: parent.height
    title: qsTr("Home")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ImageButton {
            width: 40
            height: 40
            x: 20
            y: 20
            source: "qrc:/icons/info.svg"

            onClicked: pageStack.push(Pages.aboutPageUrl)
        }

        ColumnLayout {
            anchors.centerIn: parent

            Button {
                width: parent.width / 2
                height: 40
                text: qsTr("Населені пункти України")

                onClicked: pageStack.push(Pages.localityListPageUrl)
            }
        }
    }
}
