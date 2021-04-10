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

            // Галочки із тим, що показувати

            // область пошуку

            ScrollView {
                Layout.preferredWidth: localityListPage.width
                Layout.preferredHeight: localityListPage.height - 60

                ListView {
                    clip: true
                    width: localityListPage.width
                    model: 50
                    delegate: ItemDelegate {
                        text: "Locality " + (index + 1)
                        width: localityListPage.width
                    }
                }
            }
        }
    }
}
