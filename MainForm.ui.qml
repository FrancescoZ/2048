import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    id: mainWindow
    width: 300
    height: 350


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
                height: 50
                width:50
            }
        }



    }

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


}
