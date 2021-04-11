import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "./settings"
import "./pages"
import "./components"

ApplicationWindow {
    id: window
    width: AppSettings.screenWidth
    height: AppSettings.screenHeight
    visible: true
    title: qsTr("Ukraine Guide")

    StackView {
        id: pageStack
        initialItem: Pages.homePageUrl
        anchors.fill: parent

        Keys.onBackPressed: pop()
    }

    Popup {
        id: exitConfirmationPopup
        anchors.centerIn: parent
        width: message.contentWidth + 30
        height: 200
        padding: 0
        modal: true

        background: Rectangle {
            color: Palette.popupBackgroundColor
            radius: 10
            border.width: 2
            border.color: Palette.borderColor
        }

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 50
            width: message.contentWidth

            Text {
                id: message
                text: qsTr("Ви дійсно хочете вийти з додатку?")
                font.pointSize: AppSettings.titleFontSize
                font.bold: true
                color: Palette.headerTextColor
            }

            RowLayout {
                spacing: 10
                Layout.alignment: Qt.AlignHCenter

                CustomButton {
                    Layout.preferredWidth: exitConfirmationPopup.width / 3
                    Layout.preferredHeight: 40
                    color: Palette.acceptButtonColor
                    text: qsTr("Так")
                    onClicked: Qt.quit()
                }

                CustomButton {
                    Layout.preferredWidth: exitConfirmationPopup.width / 3
                    Layout.preferredHeight: 40
                    color: Palette.declineButtonColor
                    text: qsTr("Ні")
                    onClicked: exitConfirmationPopup.close()
                }
            }
        }

    }
}
