import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import com.UkraineGuide.LocalityType 1.0

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

        ScrollView {
            anchors.fill: parent
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            ColumnLayout {
                spacing: 0

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

                Image {
                    id: previewImage
                    property int curImageIndex: 0
                    source: localityModel.previewImages[curImageIndex]
                    Layout.preferredWidth: localityDescriptionPage.width
                    Layout.preferredHeight: AppSettings.screenWidth > AppSettings.screenHeight ? // landscape
                                                localityDescriptionPage.height - header.Layout.preferredHeight :
                                                localityDescriptionPage.height / 4

                    ImageButton {
                        width: 30
                        height: 30
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.rightMargin: 5
                        source: "qrc:/icons/repeat.png"
                        visible: localityModel.numOfPreviewImages > 1

                        onClicked: {
                            if (previewImage.curImageIndex + 1 >= localityModel.numOfPreviewImages) {
                                previewImage.curImageIndex = 0
                            } else {
                                previewImage.curImageIndex++;
                            }
                        }
                    }
                }

                DescriptionBlock {
                    headerText: qsTr("Назва:")
                    valueText: localityModel.ukrName + " / " + localityModel.engName
                }

                DescriptionBlock {
                    headerText: qsTr("Дата заснування:")
                    valueText: localityModel.foundationDate + " " + qsTr("рік.")
                }

                DescriptionBlock {
                    headerText: qsTr("Область:")
                    valueText: localityModel.oblast
                    visible: valueText !== ""
                }

                DescriptionBlock {
                    headerText: qsTr("Район:")
                    valueText: localityModel.region
                    visible: valueText !== ""
                }

                DescriptionBlock {
                    headerText: qsTr("Тип:")
                    valueText: {
                        if (localityModel.type === LocalityType.CITY) {
                            return qsTr("Місто.")
                        } else if (localityModel.type === LocalityType.SETTLEMENT) {
                            return qsTr("Село міського типу.")
                        } else {
                            return qsTr("Село.")
                        }
                    }
                }

                DescriptionBlock {
                    headerText: qsTr("Населення:")
                    valueText: localityModel.population + " осіб."
                }

                DescriptionBlock {
                    headerText: qsTr("Площа:")
                    valueText: localityModel.area + " км²."
                }

                HeaderText {
                    Layout.leftMargin: 10
                    text: "Коротка інформація:"
                }

                Flickable {
                    id: flickable
                    Layout.preferredWidth: localityDescriptionPage.width
                    Layout.preferredHeight: 300

                    TextArea.flickable: TextArea {
                        text: localityModel.shortInfo
                        wrapMode: TextArea.Wrap
                        enabled: false
                    }
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
                        pageStack.push(Pages.establishmentsListPage)
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
