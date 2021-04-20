import QtQuick 2.15
import QtQuick.Layouts 1.15

import "../settings"

ColumnLayout {
    property alias headerText: header.text
    property alias valueText: value.text

    HeaderText {
        id: header
        Layout.leftMargin: 10
    }

    Text {
        id: value
        Layout.leftMargin: 20
        font.pointSize: AppSettings.blockTextFontSize
        color: Palette.blockTextColor
    }

    Separator {}
}
