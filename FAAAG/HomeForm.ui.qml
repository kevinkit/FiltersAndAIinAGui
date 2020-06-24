import QtQuick 2.15
import QtQuick.Controls 2.15
import Filters 1.0
Page {

    visible: true
    width: 1920
    height: 1080
    property alias comboBox1: comboBox1
    property alias comboBox: comboBox
    property alias imageItem: imageItem
    title: "Welcome to the filter chooser"
    transformOrigin: Item.Top

    Label {
        width: 356
        height: 44
        text: qsTr("Choose a filter ")
        anchors.verticalCenterOffset: -395
        anchors.horizontalCenterOffset: -708
        anchors.centerIn: parent
    }

    Button{
        id: loadButton
        text: "load image"
    }

    ImageItem {
        id: imageItem
        x: 220
        y: 200
        width: parent.width
        height: parent.height
        visible: true
        anchors.fill: parent
    }

    ComboBox {
        id: comboBox
        currentIndex: 0
        x: 74
        y: 162
        clip: false
        flat: false
        font.family: "Arial"
        focusPolicy: Qt.TabFocus
        enabled: true
        rotation: 0
        wheelEnabled: true

        editable: false
        textRole: "filter"

        //Filters should be done in enums
        model: ListModel {
            id: list
            ListElement {
                filter: "No filter"
                value: 0
            }
            ListElement {
                filter: "Sobel on Grayscale"
                value: 1
            }
            ListElement {
                filter: "Gaussian Blur on Grayscale"
                value: 2
            }
            ListElement {
                filter: "Median Blur"
                value: 3
            }
        }
    }

    ComboBox {
        id: comboBox1
        x: 74
        y: 217
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
