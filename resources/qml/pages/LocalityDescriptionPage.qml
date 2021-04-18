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

                    onClicked: drawer.open()
                }
            }

        }

        Drawer {
            id: drawer
            width: 0.7 * parent.width
            height: parent.height

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 20

                TextButton {
                    Layout.alignment: Text.AlignHCenter
                    text: qsTr("Показати на мапі")
                    onClicked: {
                        pageStack.push(Pages.mapViewPageUrl)
                        drawer.close()
                    }
                }

                TextButton {
                    Layout.alignment: Text.AlignHCenter
                    text: qsTr("Бронювання житла")
                    onClicked: {
                        Qt.openUrlExternally("https://www.booking.com/");
                        drawer.close()
                    }
                }

                TextButton {
                    Layout.alignment: Text.AlignHCenter
                    text: qsTr("Залізничні квитки")
                    onClicked: {
                        Qt.openUrlExternally("https://booking.uz.gov.ua/");
                        drawer.close()
                    }
                }

                TextButton {
                    Layout.alignment: Text.AlignHCenter
                    text: qsTr("Топ закладів")
                    onClicked: {
                        drawer.close()
                    }
                }

                TextButton {
                    Layout.alignment: Text.AlignHCenter
                    text: qsTr("Детальна інформація")
                    onClicked: {
                        Qt.openUrlExternally(localityModel.moreInfoUrl);
                        drawer.close()
                    }
                }
            }
        }
    }
}
