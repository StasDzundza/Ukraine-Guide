import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../settings"

Popup {
    id: confirmActionPopup
    property alias message: message.text
    anchors.centerIn: Overlay.overlay
    width: message.contentWidth + 30
    height: 200
    padding: 0
    modal: true

    signal cancelPressed()
    signal okPressed()

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
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: AppSettings.titleFontSize
            font.bold: true
            color: Palette.headerTextColor
        }

        RowLayout {
            spacing: 10
            Layout.alignment: Qt.AlignHCenter

            CustomButton {
                Layout.preferredWidth: confirmActionPopup.width / 3
                Layout.preferredHeight: 40
                color: Palette.acceptButtonColor
                text: qsTr("Так")
                onClicked: confirmActionPopup.okPressed()
            }

            CustomButton {
                Layout.preferredWidth: confirmActionPopup.width / 3
                Layout.preferredHeight: 40
                color: Palette.declineButtonColor
                text: qsTr("Ні")
                onClicked: confirmActionPopup.cancelPressed()
            }
        }
    }
}
