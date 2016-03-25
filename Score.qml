import QtQuick 2.5

Rectangle {
    id: container
    width: 100
    height: 55
    color: "#baa1a1"
    radius: 14

    property string name: "";
    property string value: "";

    Text {
        id: lblName
        x: 39
        y: 8
        font.family: "Verdana"
        text: name
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
    }

    Text {
        id: lblValue
        x: 39
        y: 26
        font.family: "Verdana"
        text: value
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 17
    }
}

