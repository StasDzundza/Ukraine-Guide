import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

Page {
    id: routePage
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Selected route")

    ConfirmActionPopup {
        id: savePopup
        message: qsTr("У вас є незбережені зміни в маршруті.\nБажаєте їх зберегти?")

        onOkPressed: {
            application.saveCurrentRoute()
            close()
            pageStack.pop()
        }
        onCancelPressed: {
            close()
            pageStack.pop()
        }
    }

    ConfirmActionPopup {
        id: confirmLocalityRemovingPopup
        property int localityIndex
        property string localityName
        message: qsTr("Ви дійсно хочете вилучити " + localityName + "\nз маршруту?")

        onOkPressed: {
            localitiesList.model.remove(localityIndex)
            close()
        }
        onCancelPressed: {
            close()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Header {
                Layout.preferredWidth: routePage.width
                Layout.preferredHeight: AppSettings.headerHeight
                title: application.currentRouteListModel.routeName
                titleColor: application.currentRouteListModel.edited ?
                                Palette.routeEditedHeaderColor :
                                Palette.headerTextColor

                ImageButton {
                    id: editButton
                    property bool editMode: false
                    sourceSize: "30x30"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    source: editMode ? "qrc:/icons/save.svg" : "qrc:/icons/edit.svg"
                    onClicked: {
                        editMode = !editMode
                        if (!editMode) {
                            application.currentRouteListModel.edited = false
                        }
                    }
                }

                onBackClicked: {
                    if (application.currentRouteListModel.edited) {
                        savePopup.open()
                    } else {
                        pageStack.pop()
                    }
                }
            }

            Button {
                text: qsTr("Додати зупинку")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: routePage.width
                visible: editButton.editMode

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
                            text: localityType === "village" ?
                                      (index + 1) + ". " + ukrName + " / " + engName + " (" + oblast + " обл.)":
                                      (index + 1) + ". " + ukrName + " / " + engName
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
                                onClicked: localitiesList.model.moveUp(index)
                            }

                            ImageButton {
                                sourceSize: "30x30"
                                source: "qrc:/icons/arrow-circle-down.svg"
                                onClicked: localitiesList.model.moveDown(index)
                            }

                            ImageButton {
                                sourceSize: "30x30"
                                source: "qrc:/icons/trash.svg"
                                onClicked: {
                                    confirmLocalityRemovingPopup.localityIndex = index
                                    confirmLocalityRemovingPopup.localityName = ukrName
                                    confirmLocalityRemovingPopup.open()
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
