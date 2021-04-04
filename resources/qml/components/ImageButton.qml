import QtQuick 2.15

import "../settings"


Image {
    id: imageButton
    width: 25
    height: 25

    signal clicked()

    MouseArea {
        anchors.fill: parent

        onClicked: parent.clicked()
    }
}

