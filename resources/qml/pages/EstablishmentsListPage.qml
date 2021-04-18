import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

import com.UkraineGuide.LocalityListModel 1.0

Page {
    id: establishmentsListPage
    property var localityModel: application.currentLocalityModel
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Establishments list")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Header {
                Layout.preferredWidth: establishmentsListPage.width
                Layout.preferredHeight: AppSettings.headerHeight
                title: qsTr("Топ закладів " + localityModel.ukrName)

                onBackClicked: pageStack.pop()
            }

            Text {
                Layout.alignment: Text.AlignHCenter
                text: qsTr("Немає інформації.")
                color: Palette.headerTextColor
                font.pointSize: AppSettings.titleFontSize
                font.bold: true
                visible: establishmentsList.model.isEmpty
            }

            ScrollView {
                Layout.preferredWidth: establishmentsListPage.width
                Layout.preferredHeight: establishmentsListPage.height - 60

                ListView {
                    id: establishmentsList
                    clip: true
                    width: establishmentsListPage.width
                    model: localityModel.establishments
                    delegate: Rectangle {
                        width: establishmentsListPage.width
                        height: 40
                        color: Palette.listElementColor
                        border.color: Palette.listElementBorderColor
                        border.width: 1

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            x: 20
                            text: index + ". " + ukrName + " / " + engName + " (" + type + ")"
                            color: Palette.blockTextColor
                            font.pointSize: AppSettings.blockTextFontSize
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally(moreInfoUrl)
                        }
                    }

                    ScrollBar.vertical: ScrollBar {
                        policy: ScrollBar.AlwaysOn
                    }
                }
            }
        }
    }
}
