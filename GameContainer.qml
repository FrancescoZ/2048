import QtQuick 2.5

Rectangle {

    property bool visibilite
    property string texte
    property int fontSize: 51

    id: rectangle1
    width: 433
    height: 433
    radius: 9
    visible: visibilite
    color: "#7b6969"
    opacity: 0.8



    Text {
        id: text1
        x: 84
        y: 141
        width: 313
        height: 59
        color: "#000000"
        text: texte
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        visible: true
        textFormat: Text.PlainText
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: fontSize
    }


}

