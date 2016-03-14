import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 300
    height: 350
    title: qsTr("2048")

    Image {
        id: startButton
        objectName: "startButton"
        x: 35
        y: 19
        width: 36
        height: 36
        source: "play.png"

        signal playSignal()

        MouseArea {
            id: playArea
            anchors.fill: parent
            onClicked: startButton.playSignal
        }
    }

    Grid {
        id: gameTable
        objectName: "gameTable"
        x: 0
        y: 42
        width: 250
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        rows: 4
        columns: 4

        Repeater {
            id: repBox
            objectName: "repBox"

            model:16
            Box{
                boxValue: viewTable.boxes[index/4][index%4].getValue()
                height: 50
                width:50

            }
        }

    }




}

