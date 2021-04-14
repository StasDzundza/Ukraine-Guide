import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

import com.UkraineGuide.LocalityListModel 1.0

Page {
    id: localityListPage
    property var localityListModel
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Locality list")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Header {
                Layout.preferredWidth: localityListPage.width
                Layout.preferredHeight: AppSettings.headerHeight
                title: qsTr("Населені пункти України")

                onBackClicked: pageStack.pop()
            }

            Switch {
                id: showOnlyCitiesSwitch
                Layout.leftMargin: 10
                text: qsTr("Показувати тільки міста")
                checked: false
            }

            Rectangle {
                id: searchArea
                Layout.preferredWidth: localityListPage.width - 20
                Layout.preferredHeight: 40
                Layout.alignment: Qt.AlignHCenter
                color: "transparent"
                border.color: Palette.borderColor
                border.width: 1
                radius: 10

                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                    spacing: 5

                    ImageButton {
                        id: searchImage
                        anchors.verticalCenter: parent.verticalCenter
                        width: 20
                        height: 20
                        source: "qrc:/icons/search.svg"
                        onClicked: searchField.forceActiveFocus()
                    }

                    TextInput {
                        id: searchField
                        anchors.verticalCenter: parent.verticalCenter
                        width: localityListPage.width - searchImage.width - clearInput.width - 50
                        color: Palette.blockTextColor
                        font.pointSize: AppSettings.blockTextFontSize
                        wrapMode: TextInput.Wrap
                        maximumLength: 20

                        onDisplayTextChanged: localityListModel.fillSearchModel(displayText, searchModel)
                    }

                    ImageButton {
                        id: clearInput
                        anchors.verticalCenter: parent.verticalCenter
                        width: 20
                        height: 20
                        source: "qrc:/icons/edit-clear.svg"
                        onClicked: searchField.text = ""
                    }
                }
            }

            Text {
                Layout.alignment: Text.AlignHCenter
                text: qsTr("Список порожній.")
                color: Palette.headerTextColor
                font.pointSize: AppSettings.titleFontSize
                font.bold: true
                visible: localityList.model.isEmpty
            }

            LocalityListModel {
                id: searchModel
            }

            ScrollView {
                Layout.preferredWidth: localityListPage.width
                Layout.preferredHeight: localityListPage.height - 60

                ListView {
                    id: localityList
                    clip: true
                    width: localityListPage.width
                    model: searchField.displayText === "" ? localityListModel : searchModel
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

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                searchField.focus = false
                                application.loadLocalityModel(keyName)
                                pageStack.push(Pages.localityDescriptionPageUrl)
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
