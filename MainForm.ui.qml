import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    id: mainWindow
    width: 300
    height: 350

    property alias gameTable: gameTable
    property alias playArea: playArea
    property alias startButton: startButton

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
        spacing: 10
        rows: 4
        columns: 4
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
        }
        Box{
            width:50
            height:50
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
            onClicked: startButton.playSignal()

        }
    }


}