import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

import com.UkraineGuide.LocalityListModel 1.0
import com.UkraineGuide.SelectedLocalitiesModel 1.0

Page {
    id: creatingRoutePage
    property var localityListModel: application.localityListModel
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Creating route")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Header {
                Layout.preferredWidth: creatingRoutePage.width
                Layout.preferredHeight: AppSettings.headerHeight
                title: qsTr("Населені пункти України")
                onBackClicked: pageStack.pop()

                ImageButton {
                    sourceSize: "30x30"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    source: "qrc:/icons/save.svg"

                    ToolTip { id: toolTip }

                    onClicked: {
                        if (routeName.displayText !== "") {
                            if (application.routesListModel.contains(routeName.displayText)) {
                                toolTip.show("Маршрут з таким іменем вже існує!", 1000)
                            } else {
                                application.createRoute(routeName.displayText, selectedLocalities.selectedLocalities)
                                pageStack.pop()
                            }
                        } else {
                            toolTip.show("Введіть назву маршруту!", 1000)
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
                id: routeNameArea
                Layout.preferredWidth: creatingRoutePage.width - 20
                Layout.preferredHeight: 40
                Layout.alignment: Qt.AlignHCenter
                color: "transparent"
                border.color: Palette.borderColor
                border.width: 1
                radius: 10

                TextInput {
                    id: routeName
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: Palette.blockTextColor
                    font.pointSize: AppSettings.blockTextFontSize
                    wrapMode: TextInput.Wrap
                    maximumLength: 20

                    Placeholder {
                        text: "Назва маршруту..."
                        anchors.centerIn: parent
                    }
                }
            }

            Rectangle {
                id: searchArea
                Layout.preferredWidth: creatingRoutePage.width - 20
                Layout.preferredHeight: 40
                Layout.alignment: Qt.AlignHCenter
                color: "transparent"
                border.color: Palette.listElementColor
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
                        width: creatingRoutePage.width - searchImage.width - clearInput.width - 50
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
                Layout.preferredWidth: creatingRoutePage.width
                Layout.preferredHeight: creatingRoutePage.height - 200

                ListView {
                    id: localityList
                    clip: true
                    width: creatingRoutePage.width
                    model: searchField.displayText === "" ? localityListModel : searchModel

                    delegate: Rectangle {
                        width: creatingRoutePage.width
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
                                console.log("checked changed to " + checked + " !!!!!!!!!!!!!!!!!")
                                if (checked) {
                                    console.log("true !!!!!!!!!!!!!!!!!")
                                    selectedLocalities.append(keyName)
                                    console.log("added !!!!!!!!!!!!!!!!!")
                                } else {
                                    console.log("false !!!!!!!!!!!!!!!!!")
                                    selectedLocalities.remove(keyName)
                                    console.log("removed !!!!!!!!!!!!!!!!!")
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
