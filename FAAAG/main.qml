import QtQuick 2.15
import QtQuick.Controls 2.15
import Filters 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Stack")

    StackView {
        id: stackView
        width: 1920
        height: 1080
        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }


    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.2
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Live View")
                width: parent.width
                onClicked: {
                    console.log("you pushed....")
                    stackView.push("Page1Form.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Deep Learning Models")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }





    HomeForm{
        comboBox.onActivated: { imageItem.currentFilter = comboBox.currentText
                                imageItem.index = comboBox.currentIndex
                                //imageItem.executeFiltering()
        }
        comboBox1.onActivated: {
                                imageItem.representation = comboBox1.currentIndex

                                //if the representation is changed the filter is reset
                               //comboBox.currentText = "No filter"
                                //comboBox.currentIndex = 0
        }


        fileDialog.onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            imageItem.updateImage(fileDialog.fileUrls)
            comboBox1.currentIndex = 0
            imageItem.index = 0

            comboBox1.currentText = "RGB"
            imageItem.currentFilter = "RGB"

            comboBox.currentText = "No filter"
            comboBox.currentIndex = 0
        }
        fileDialog.onRejected: {
            console.log("Canceled")
        }

        loadButton {
            onClicked: fileDialog.visible = true
        }

    }

}
