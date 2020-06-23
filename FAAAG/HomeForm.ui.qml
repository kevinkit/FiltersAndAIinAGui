import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    width: 1920
    height: 1080
    title: "Welcome to the filter chooser"
    transformOrigin: Item.Top

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
        source: "image://live/image"
        fillMode: Image.PreserveAspectFit
        //fillMode: Image.PreserveAspectFit

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
        //        displayText: "Choose a filter"
        editable: false
        textRole: "filter"

        //Filters should be done in enums
        model: ListModel {
            id: list
            ListElement {
                filter: "Laplace"
                value: 0
            }
            ListElement {
                filter: "Gaussian Blur"
                value: 1
            }
            ListElement {
                filter: "Median Blur"
                value: 2
            }
        }

        onActivated: Filters.currentFilter = currentText

        Connections {
            target: comboBox
            onClicked: print("clicked")
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
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/

