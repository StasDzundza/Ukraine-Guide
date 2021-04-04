import QtQuick 2.15

import "../settings"


Image {
    id: imageButton

    signal clicked()

    MouseArea {
        anchors.fill: parent

        onClicked: parent.clicked()
    }
}

