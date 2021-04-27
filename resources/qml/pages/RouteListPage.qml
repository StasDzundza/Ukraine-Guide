import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"
import "../components"

Page {
    id: routesListPage
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Routes list")

    ConfirmActionPopup {
        id: confirmRouteRemovingPopup
        property string routeName
        property int routeIndex
        message: qsTr("Ви дійсно хочете видалити\nмаршрут " + routeName + "?")

        onOkPressed: {
            application.removeRoute(routeIndex)
            close()
        }
        onCancelPressed: close()
    }

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            Header {
                Layout.preferredWidth: routesListPage.width
                Layout.preferredHeight: AppSettings.headerHeight
                title: qsTr("Мої маршрути")

                ImageButton {
                    sourceSize: "30x30"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    source: "qrc:/icons/create.svg"
                    onClicked: pageStack.push(Pages.creatingRoutePageUrl)
                }

                onBackClicked: pageStack.pop()
            }

            Text {
                Layout.alignment: Text.AlignHCenter
                text: qsTr("Список порожній.")
                color: Palette.headerTextColor
                font.pointSize: AppSettings.titleFontSize
                font.bold: true
                visible: routesList.model.isEmpty
            }

            ScrollView {
                Layout.preferredWidth: routesListPage.width
                Layout.preferredHeight: routesListPage.height - 60

                ListView {
                    id: routesList
                    clip: true
                    width: routesListPage.width
                    model: application.routesListModel

                    delegate: Rectangle {
                        width: routesListPage.width
                        height: 40
                        color: Palette.listElementColor
                        border.color: Palette.listElementBorderColor
                        border.width: 1

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            x: 20
                            text: routeName
                            color: Palette.blockTextColor
                            font.pointSize: AppSettings.blockTextFontSize
                        }

                        ImageButton {
                            sourceSize: "30x30"
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 20
                            source: "qrc:/icons/trash.svg"

                            onPressed: {
                                confirmRouteRemovingPopup.routeIndex = index
                                confirmRouteRemovingPopup.routeName = routeName
                                confirmRouteRemovingPopup.open()
                            }
                        }

                        MouseArea {
                            height: parent.height
                            width: parent.width - 50

                            onClicked: {
                                application.loadCurrentRoute(routeName)
                                pageStack.push(Pages.routePageUrl, {"routeName": routeName})
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
