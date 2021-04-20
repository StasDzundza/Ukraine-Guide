import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

Page {
    objectName: "homePage"
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
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

        ImageButton {
            width: 40
            height: 40
            anchors.right: parent.right
            anchors.rightMargin: 20
            y: 20
            source: "qrc:/icons/exit.svg"

            onClicked: exitConfirmationPopup.open()
        }

        ColumnLayout {
            spacing: 20
            anchors.centerIn: parent

            Button {
                text: qsTr("Населені пункти України")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: AppSettings.screenWidth * 0.66

                onClicked: pageStack.push(Pages.localityListPageUrl, {"localityListModel": application.localityListModel})
            }

            Button {
                text: qsTr("Улюблені місця")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: AppSettings.screenWidth * 0.66

                onClicked: pageStack.push(Pages.localityListPageUrl, {"localityListModel": application.favoriteFocalityListModel})
            }
        }
    }
}
