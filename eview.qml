import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import Esri.Samples 1.0
import Esri.ArcGISExtras 1.1

DisplaySceneLayerGUI {
    id: displaySceneLayerGUI
    width: 1024
    height: 800

    property double scaleFactor: System.displayScaleFactor

    // add a mapView component
    SceneView {
        anchors.fill: parent
        objectName: "sceneView"
    }

    RowLayout {
        id: layout
        //anchors.fill: parent
        spacing: 6
        Layout.maximumHeight: 80
        Layout.fillWidth: true

        ComboBox {
            id: comboBoxBasemap
            objectName: "comboBoxBasemap"
            anchors {
//                left: parent.left
//                top: parent.top
                margins: 15 * scaleFactor
            }
//            width: 175 * scaleFactor
            //width: 275
            Layout.minimumWidth: 300
            model: ["Topographic","Streets","Imagery","Oceans"]
            onCurrentTextChanged: {
                // Call C++ invokable function to switch the basemaps
                displaySceneLayerGUI.changeBasemap(currentText);
            }
        }

        Button {
            id: elv_button
            objectName: "elv_button"
            Layout.minimumWidth: 100
            anchors {
                //left: parent.left
                //top: parent.top
                topMargin: 8
                margins: 15 * scaleFactor
            }
            checkable: true
             text: "Elevation"
//             Layout.row: 1                       // item in the second row of the column
//             Layout.alignment: Qt.AlignCenter    // simple center the button in its spatial slot
             onClicked:{
                displaySceneLayerGUI.elevationChanged(elv_button.checked)
             }
         }

        Button {
            id: layer_btn_1
            objectName: "layer_btn_1"
            Layout.minimumWidth: 100
            anchors {
                //left: parent.left
                //top: parent.top
                topMargin: 8
                margins: 15 * scaleFactor
            }
            checkable: true
             text: "ok"
//             Layout.row: 1                       // item in the second row of the column
//             Layout.alignment: Qt.AlignCenter    // simple center the button in its spatial slot
             onClicked:{
                displaySceneLayerGUI.loadLayer(objectName, layer_btn_1.checked)
             }
         }
        Button {
            id: layer_btn_2
            objectName: "layer_btn_2"
            Layout.minimumWidth: 100
            checkable: true
            anchors {
                //topMargin: 8
                //left: parent.left
                //top: parent.top
                margins: 15 * scaleFactor
            }
             text: "ok"
//             Layout.row: 1                       // item in the second row of the column
//             Layout.alignment: Qt.AlignCenter    // simple center the button in its spatial slot
             onClicked:{
                displaySceneLayerGUI.loadLayer(objectName, layer_btn_2.checked)
             }
         }
        Button {
            id: layer_btn_3
            objectName: "layer_btn_3"
            Layout.minimumWidth: 100
            checkable: true
             text: "ok"
             onClicked:{
                displaySceneLayerGUI.loadLayer(objectName, layer_btn_3.checked)
             }
         }
        Button {
            id: layer_btn_4
            objectName: "layer_btn_4"
            Layout.minimumWidth: 100
            checkable: true
             text: "ok"
             onClicked:{
                displaySceneLayerGUI.loadLayer(objectName, layer_btn_4.checked)
             }
         }
        Button {
            id: layer_btn_5
            objectName: "layer_btn_5"
            Layout.minimumWidth: 100
            checkable: true
             text: "ok"
             onClicked:{
                displaySceneLayerGUI.loadLayer(objectName, layer_btn_5.checked)
             }
         }
        Button {
            id: layer_btn_6
            objectName: "layer_btn_6"
            Layout.minimumWidth: 100
            checkable: true
             text: "ok"
             onClicked:{
                displaySceneLayerGUI.loadLayer(objectName, layer_btn_6.checked)
             }
         }

    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border {
            width: 0.5 * scaleFactor
            color: "black"
        }
    }

}


