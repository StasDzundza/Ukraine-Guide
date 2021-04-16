import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

Page {
    id: localityDescriptionPage
    property var localityModel: application.currentLocalityModel
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Locality list")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Rectangle {
                id: header
                property string title: qsTr("Header")
                Layout.preferredWidth: localityDescriptionPage.width
                Layout.preferredHeight: AppSettings.headerHeight
                color: Palette.headerColor

                ImageButton {
                    id: backButton
                    source: "qrc:/icons/arrow-back.svg"
                    anchors.verticalCenter: parent.verticalCenter
                    x: 10 // left margin

                    onClicked: pageStack.pop()
                }

                ImageButton {
                    width: 30
                    height: 30
                    source: localityModel.isFavorite ? "qrc:/icons/fill-star.svg" : "qrc:/icons/star.svg"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: title.left
                    anchors.rightMargin: 15

                    onClicked: localityModel.changeFavoriteStatus()
                }

                Text {
                    id: title
                    text: localityModel.ukrName
                    anchors.centerIn: parent
                    color: Palette.headerTextColor
                    font.pointSize: AppSettings.titleFontSize
                    font.bold: true
                }

                ImageButton {
                    width: 30
                    height: 30
                    source: "qrc:/icons/menu.svg"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: header.right
                    anchors.rightMargin: 10

                    onClicked: {
                        pageStack.push(Pages.mapViewPageUrl)
                        // TODO open menu or side bar with options
                    }
                }
            }
        }
    }
}
