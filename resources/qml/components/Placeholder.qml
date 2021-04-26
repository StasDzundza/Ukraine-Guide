import QtQuick 2.15

import "../settings"

Text {
    visible: parent.displayText === ""
    color: Palette.placeholderTextColor
    font.pointSize: AppSettings.placeholderFontSize
}
