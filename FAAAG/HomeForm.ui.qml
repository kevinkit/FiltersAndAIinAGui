import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    width: 1920
    height: 1080
    transformOrigin: Item.Top

    title: qsTr("Home")

    Label {
        width: 356
        height: 44
        text: qsTr("You are on the homeasd")
        anchors.verticalCenterOffset: -467
        anchors.horizontalCenterOffset: -519
        anchors.centerIn: parent
    }

    Image {
        id: image
        x: 254
        y: 162
        width: 1352
        height: 670
        source: "images/images/1.png"
        fillMode: Image.Tile
        //fillMode: Image.PreserveAspectFit
    }

    ComboBox {
        id: comboBox
        x: 74
        y: 162
    }

    ComboBox {
        id: comboBox1
        x: 74
        y: 217
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
