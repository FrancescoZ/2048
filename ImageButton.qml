import QtQuick 2.5

Rectangle{
    id:cont
    signal clicked
    property string imageSource: "play.png"

    Image {
        id: button
        anchors.fill: parent
        source:imageSource
    }

    MouseArea {
        id: clickArea
        anchors.fill: parent
        onClicked: cont.clicked();
        hoverEnabled: true;
    }
}
