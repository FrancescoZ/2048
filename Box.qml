import QtQuick 2.0

Item {
    id: item1
    width: 50
    height: 50

    property alias boxColor: box.color
    property alias boxBorderColor: box.border.color
    property alias boxVisible: box.visible
    property alias boxValue: value.text


    MouseArea {
        id: mouseArea
        anchors.fill: parent

        Rectangle {
            id:box
            radius: 7
            border.width: 2
            anchors.fill: parent

            Text {
                id: value
                color: "#ffffff"
                z: 1
                styleColor: "#ffffff"
                font.bold: true
                font.family: "Tahoma"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.bottomMargin: 10
                anchors.topMargin: 10
                anchors.fill: parent
                font.pixelSize: 38
            }
        }
    }

}

