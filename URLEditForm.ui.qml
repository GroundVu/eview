import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400

    ColumnLayout {
        id: columnLayout1
        x: 56
        y: 192
        width: 260
        height: 137
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        RowLayout {
            id: rowLayout1
            Layout.fillWidth: true
            anchors.bottomMargin: 241
            anchors.fill: parent
            transformOrigin: Item.Center

        }

        TextField {
            id: textField1
            text: qsTr("Text Field")
        }
    }

    Label {
        id: label1
        text: qsTr("Label")
    }
}
