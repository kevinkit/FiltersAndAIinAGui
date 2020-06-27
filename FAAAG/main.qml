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

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
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
            comboBox.currentIndex = 0
            imageItem.index = 0
        }
        fileDialog.onRejected: {
            console.log("Canceled")
        }

        loadButton {
            onClicked: fileDialog.visible = true
        }

    }

}
