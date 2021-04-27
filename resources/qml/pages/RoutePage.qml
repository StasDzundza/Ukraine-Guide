import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

Page {
    id: routePage
    property string routeName: value
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Selected route")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Header {
                Layout.preferredWidth: routePage.width
                Layout.preferredHeight: AppSettings.headerHeight
                title: routeName

                ImageButton {
                    id: editButton
                    property bool editMode: false
                    sourceSize: "30x30"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    source: editMode ? "qrc:/icons/save.svg" : "qrc:/icons/edit.svg"
                    onClicked: editMode = !editMode
                }

                onBackClicked: pageStack.pop()
            }

            Button {
                text: qsTr("Додати зупинку")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: routePage.width

                onClicked: {
                    // TODO open adding localities
                }
            }

            Text {
                Layout.alignment: Text.AlignHCenter
                text: qsTr("Маршрут порожній.")
                color: Palette.headerTextColor
                font.pointSize: AppSettings.titleFontSize
                font.bold: true
                visible: localitiesList.model.isEmpty
            }

            ScrollView {
                Layout.preferredWidth: routePage.width
                Layout.preferredHeight: routePage.height - 60

                ListView {
                    id: localitiesList
                    clip: true
                    width: routePage.width
                    model: application.currentRouteListModel

                    delegate: Rectangle {
                        width: routePage.width
                        height: 40
                        color: Palette.listElementColor
                        border.color: Palette.listElementBorderColor
                        border.width: 1

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            x: 20
                            text: (index + 1) + ". " + ukrName + " / " + engName
                            color: Palette.blockTextColor
                            font.pointSize: AppSettings.blockTextFontSize
                        }

                        RowLayout {
                            spacing: 10
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 20
                            visible: editButton.editMode

                            ImageButton {
                                sourceSize: "30x30"
                                source: "qrc:/icons/arrow-circle-up.svg"
                                onClicked: {
                                    localitiesList.model.moveUp(index)
                                }
                            }

                            ImageButton {
                                sourceSize: "30x30"
                                source: "qrc:/icons/arrow-circle-down.svg"
                                onClicked: {
                                    localitiesList.model.moveDown(index)
                                }
                            }

                            ImageButton {
                                sourceSize: "30x30"
                                source: "qrc:/icons/trash.svg"
                                onClicked: {
                                    // TODO show confirmation popup
                                }
                            }
                        }

                        MouseArea {
                            height: parent.height
                            width: editButton.editMode ? parent.width - 130 : parent.width

                            ToolTip { id: toolTip }

                            onClicked: {
                                if (editButton.editMode) {
                                    toolTip.show("Завершіть редагування.", 1000)
                                } else {
                                    application.loadLocalityModel(keyName)
                                    pageStack.push(Pages.localityDescriptionPageUrl)
                                }
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
