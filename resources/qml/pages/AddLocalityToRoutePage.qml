import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

import com.UkraineGuide.LocalityListModel 1.0
import com.UkraineGuide.SelectedLocalitiesModel 1.0

Page {
    id: addLocalityToRoutePage
    property var localityListModel: application.localityListModel
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Add locality to route")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Header {
                Layout.preferredWidth: addLocalityToRoutePage.width
                Layout.preferredHeight: AppSettings.headerHeight
                title: qsTr("Виберіть нові зупинки")
                onBackClicked: pageStack.pop()

                ImageButton {
                    sourceSize: "30x30"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    source: "qrc:/icons/save.svg"

                    ToolTip { id: toolTip }

                    onClicked: {
                        if (!selectedLocalities.isEmpty) {
                            application.addLocalitiesToCurrentRoute(selectedLocalities.selectedLocalities)
                            pageStack.pop()
                        } else {
                            toolTip.show("Ви нічого не обрали!", 1000)
                        }
                    }
                }
            }

            Switch {
                id: showOnlyCitiesSwitch
                Layout.leftMargin: 10
                text: qsTr("Показувати тільки міста")
                checked: false
            }

            Rectangle {
                id: searchArea
                Layout.preferredWidth: addLocalityToRoutePage.width - 20
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
                        width: addLocalityToRoutePage.width - searchImage.width - clearInput.width - 50
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
                text: qsTr("Нічого не знайдено.")
                color: Palette.headerTextColor
                font.pointSize: AppSettings.titleFontSize
                font.bold: true
                visible: localityList.model.isEmpty
            }

            LocalityListModel {
                id: searchModel
            }

            SelectedLocalitiesModel {
                id: selectedLocalities
            }

            ScrollView {
                Layout.preferredWidth: addLocalityToRoutePage.width
                Layout.preferredHeight: addLocalityToRoutePage.height - 100

                ListView {
                    id: localityList
                    clip: true
                    width: addLocalityToRoutePage.width
                    model: searchField.displayText === "" ? localityListModel : searchModel

                    delegate: Rectangle {
                        width: addLocalityToRoutePage.width
                        height: 40
                        color: Palette.listElementColor
                        border.color: Palette.listElementBorderColor
                        border.width: 1
                        visible: localityType === "city" || !showOnlyCitiesSwitch.checked

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            x: 20
                            text: localityType === "village" ?
                                      ukrName + " / " + engName + " (" + oblast + " обл.)":
                                      ukrName + " / " + engName
                            color: Palette.blockTextColor
                            font.pointSize: AppSettings.blockTextFontSize
                        }

                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 20
                            checked: selectedLocalities.contains(keyName)

                            onCheckedChanged: {
                                if (checked) {
                                    selectedLocalities.append(keyName)
                                } else {
                                    selectedLocalities.remove(keyName)
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
