import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0
import Filters 1.0

Page {

    visible: true
    width: 1920
    height: 1080
    property alias checkBox1: checkBox1
    property alias checkBox: checkBox
    property alias loadButton: loadButton
    property alias comboBox1: comboBox1
    property alias comboBox: comboBox
    property alias imageItem: imageItem
    property alias fileDialog: fileDialog
    title: "Welcome to the filter chooser"
    transformOrigin: Item.Top

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: ["Image files (*.jpg *.png,*.jpeg,*.tiff)", "All files (*)"]
        Component.onCompleted: visible = false
    }

    Label {
        width: 356
        height: 44
        text: qsTr("Choose a filter ")
        anchors.verticalCenterOffset: -395
        anchors.horizontalCenterOffset: -708
        anchors.centerIn: parent
    }

    CheckBox{
        id: checkBox
        x: 74
        y: 339

    }

    Button {
        id: loadButton
        x: 74
        y: 60
        width: 135
        height: 40
        text: "load image"
    }

    ImageItem {
        id: imageItem
        x: comboBox.x + comboBox.width + 20
        y: comboBox.y
        width: parent.width*0.8
        height: parent.height*0.8
        visible: true
        //anchors.fill: parent
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
                filter: "Sobel"
                value: 1
            }
            ListElement {
                filter: "Gaussian Blur"
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
        currentIndex: 0
        x: 74
        y: 265
        clip: false
        flat: false
        font.family: "Arial"
        focusPolicy: Qt.TabFocus
        enabled: true
        rotation: 0
        wheelEnabled: true

        editable: false
        textRole: "representation"

        model: ListModel {
            id: applyChooser
            ListElement {
                representation: "RGB"
                value: 0
            }
            ListElement {
                representation: "Grayscale"
                value: 1
            }
            ListElement {
                representation: "DFT Magnitude"
                value: 2
            }
        }
    }

    Label {
        width: 356
        height: 44
        text: qsTr("Choose a representation")
        anchors.verticalCenterOffset: -288
        anchors.horizontalCenterOffset: -708
        anchors.centerIn: parent
    }

    Label {
        width: 356
        height: 44
        text: qsTr("Live Camera")
        anchors.verticalCenterOffset: -166
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -656
    }

    CheckBox {
        id: checkBox1
        x: 74
        y: 396
    }


    Label {
        width: 356
        height: 44
        text: qsTr("Use Deep Learning")
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -108
        anchors.horizontalCenterOffset: -656
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
