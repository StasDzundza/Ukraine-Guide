import QtQuick 2.15

import "../settings"

Image {
    id: imageButton

    signal clicked()
    signal pressed()

    MouseArea {
        anchors.fill: parent

        onClicked: parent.clicked()
        onPressed: parent.pressed()
    }
}

