import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

Page {
    id: localityListPage
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Locality list")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Header {
                Layout.preferredWidth: localityListPage.width
                Layout.preferredHeight: 50
                title: qsTr("Населені пункти України")

                onBackClicked: pageStack.pop()
            }

            Switch {
                id: showOnlyCitiesSwitch
                Layout.leftMargin: 10
                text: qsTr("Показувати тільки міста")
                checked: false
            }

            // область пошуку

            ScrollView {
                Layout.preferredWidth: localityListPage.width
                Layout.preferredHeight: localityListPage.height - 60

                ListView {
                    clip: true
                    width: localityListPage.width
                    model: application.localityListModel
                    delegate: Rectangle {
                        width: localityListPage.width
                        height: 40
                        color: Palette.listElementColor
                        border.color: Palette.listElementBorderColor
                        border.width: 1
                        visible: localityType === "city" || !showOnlyCitiesSwitch.checked

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            x: 20
                            text: ukrName
                            color: Palette.blockTextColor
                            font.pointSize: AppSettings.blockTextFontSize
                        }

                        ImageButton {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 20
                            source: "qrc:/icons/more-line.svg"
                            onClicked: { // TODO open more menu
                            }
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
