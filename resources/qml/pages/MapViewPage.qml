import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtLocation 5.15
import QtPositioning 5.15

import "../settings"
import "../components"

Page {
    id: mapViewPage
    property var localityModel: application.currentLocalityModel
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    title: qsTr("Locality list")

    Rectangle {
        anchors.fill: parent
        color: Palette.backgroundColor

        ColumnLayout {
            spacing: 0

            Header {
                id: header
                Layout.preferredWidth: mapViewPage.width
                Layout.preferredHeight: AppSettings.headerHeight
                title: localityModel.ukrName

                RowLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    spacing: 10

                    ImageButton {
                        id: leftArrow
                        Layout.preferredWidth: 30
                        Layout.preferredHeight: 30
                        source: "qrc:/icons/arrow-left-circle.svg"

                        onClicked: {
                            if (map.curMapTypeIndex - 1 >= 0) {
                                map.curMapTypeIndex = map.curMapTypeIndex - 1
                            } else {
                                map.curMapTypeIndex = map.supportedMapTypes.length - 1
                            }
                        }
                    }

                    ImageButton {
                        id: rightArrow
                        Layout.preferredWidth: 30
                        Layout.preferredHeight: 30
                        source: "qrc:/icons/arrow-right-circle.svg"

                        onClicked: {
                            if (map.curMapTypeIndex + 1 < map.supportedMapTypes.length) {
                                map.curMapTypeIndex = map.curMapTypeIndex + 1
                            } else {
                                map.curMapTypeIndex = 0
                            }
                        }
                    }
                }

                onBackClicked: pageStack.pop()
            }

            Plugin {
                id: mapPlugin
                name: "osm" // geoservices provider (open steet map is used)
            }

            Map {
                id: map
                property int curMapTypeIndex: 5
                Layout.preferredWidth: mapViewPage.width
                Layout.preferredHeight: mapViewPage.height - header.Layout.preferredHeight
                activeMapType: supportedMapTypes[curMapTypeIndex]
                plugin: mapPlugin
                center: QtPositioning.coordinate(localityModel.coordinates.x, localityModel.coordinates.y)
                zoomLevel: 12
                copyrightsVisible: false
            }
        }
    }
}
