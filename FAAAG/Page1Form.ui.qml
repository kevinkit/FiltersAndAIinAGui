import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    width: 1920
    height: 1080

    title: qsTr("Page 1")

    Label {
        width: 356
        height: 44
        text: qsTr("Choose a filter ")
        anchors.verticalCenterOffset: -395
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -708
    }

    ComboBox {
        id: comboBox
        x: 74
        y: 162
        currentIndex: 0
        clip: false
        rotation: 0
        font.family: "Arial"
        model: ListModel {
            id: list
            ListElement {
                value: 0
                filter: "No filter"
            }

            ListElement {
                value: 1
                filter: "Sobel"
            }

            ListElement {
                value: 2
                filter: "Gaussian Blur"
            }

            ListElement {
                value: 3
                filter: "Median Blur"
            }
        }
        flat: false
        focusPolicy: Qt.TabFocus
        enabled: true
        textRole: "filter"
        editable: false
        wheelEnabled: true
    }

    ComboBox {
        id: comboBox1
        x: 74
        y: 265
        currentIndex: 0
        clip: false
        rotation: 0
        font.family: "Arial"
        model: ListModel {
            id: applyChooser
            ListElement {
                value: 0
                filter: "RGB"
            }

            ListElement {
                value: 1
                filter: "Grayscale"
            }

            ListElement {
                value: 2
                filter: "DFT Magnitude"
            }
        }
        flat: false
        focusPolicy: Qt.TabFocus
        enabled: true
        textRole: "filter"
        editable: false
        wheelEnabled: true
    }

    Label {
        width: 356
        height: 44
        text: qsTr("Choose a representation")
        anchors.verticalCenterOffset: -288
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -708
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
