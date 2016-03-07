import QtQuick 2.0

Item {
    id: item1
    width: 50
    height: 50

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        Rectangle {
            id:box
            color: viewBoxItem.boxColor
            radius: 7
            visible: viewBoxItem.boxVisible
            border.width: 2
            border.color: viewBoxItem.boxBorder
            anchors.fill: parent

            Text {
                id: value
                color: "#ffffff"
                text: viewBoxItem.boxValue
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

    Rectangle {
        id: rectangle1
        color: "#ada9a9"
        z: -2
        anchors.fill: parent
    }

}
