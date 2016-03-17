import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Rectangle {
    visible: true
    width: 500
    height: 600

    ImageButton{
        id:startGame
        x: 219
        y: 14
        width: 83
        height: 83
        imageSource:"play.png"
        onClicked: {
            gamer.deleteCells();
            gamer.startGame();
            gameContainer.visibilite=false;
            //rectangle1.foco=true;
        }
    }

    Rectangle {
        id: header
        x: 5
        y: 7

        property bool foco: true

        width: 193
        height: 96
        color: "#eec22e"
        radius: 15
        focus: foco

        Keys.onPressed: {
                switch (event.key){
                case Qt.Key_Up:
                    gamer.up();
                    break;
                case Qt.Key_Down:
                    gamer.down();
                    break;
                case Qt.Key_Left:
                    gamer.left();
                    break;
                case Qt.Key_Right:
                    gamer.right();
                    break;
                }
                /* if(gamer.getScore()*1 > 20000 && gamer.getMaxValue() == 2048 && !gamer.getWin())
               {
                    gameContainer.visibilite=true;
                    gameContainer.texte="Winner\n Keep going?";
                    header.foco=false;
                }*/
                if(!gamer.gameStatus())
                {
                    gameContainer.visibilite=true;
                    gameContainer.texte="End of Game";
                    header.foco=false;

                }
        }

        Text {
            id: title
            x: 18
            y: 39
            text: qsTr("2048")
            font.family: "Verdana"
            rotation: 0
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: true
            font.pixelSize: 56
            color: "#f7f8f0"
        }
        MouseArea{
            anchors.fill: parent;
            onClicked:
            {
                gamerContainer.visibilite=true;
                gamerContainer.texte="Developped by: \Francesco Zanoli\nMilter Shiniti Pesce";

            }

            Text {
                id: text2
                x: 108
                y: 79
                width: 92
                height: 9
                color: "#f1eded"
                text: qsTr("for Hacker")
                font.bold: true
                font.pixelSize: 10
            }
        }

    }

    GridBox {
        id: grid
        height: 450
        width: 450
        anchors.rightMargin: 19
        anchors.bottomMargin: 23
        anchors.leftMargin: 22
        anchors.topMargin: 121
        col: 4
        row: 4
        objectName: "grid"
    }

    GameContainer {
        id: gameContainer
        x: 36
        y: 134
        anchors.leftMargin: -177
        visibilite: false
        texte: "Game Over"
        MouseArea {
            anchors.fill: parent;
            onClicked: {
                parent.visibilite=false;
                if (gamer.getScore()*1 > 20000 && gamer.getMaxValue() == 2048)gamer.gagnant();
            }
        }


    }
}






