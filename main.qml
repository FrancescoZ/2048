import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Rectangle {
    visible: true
    width: 500
    height: 700

    ImageButton{
        id:startGame
        x: 34
        y: 116
        width: 83
        height: 83
        imageSource:"play.jpg"
        onClicked: {

            gamer.startGame();
            gameContainer.visibilite=false;
            header.foco=true;
        }
    }

    ImageButton {
        id: undo
        x: 123
        y: 127
        width: 61
        height: 62
        imageSource: "back.png"
        onClicked: {
            if (gamer.gameStatus())
                gamer.undo();
        }
    }

    ImageButton {
        id: save
        x: 203
        y: 127
        width: 61
        height: 62
        imageSource: "save.jpg"
        onClicked: {
            if (gamer.gameStatus())
                gamer.saveGame();
        }
    }
    ImageButton {
        id: open
        x: 270
        y: 127
        width: 61
        height: 62
        imageSource: "open.png"
        onClicked: {
            if (gamer.gameStatus())
                gamer.loadGame();
        }
    }

    ImageButton {
        id: plus
        x: 418
        y: 127
        width: 61
        height: 62
        imageSource: "plus.png"
        onClicked: {
           gamer.setTaille(gamer.getTaille+1);
        }
    }

    ImageButton {
        id: moin
        x: 351
        y: 148
        width: 61
        height: 19
        imageSource: "minus.jpg"
        onClicked: {
           gamer.setTaille(gamer.getTaille-1);
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
            if(!gamer.animRunning())
            {
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
               if(gamer.getMaxValue() == 2048 && !gamer.getWin())
               {
                    gameContainer.visibilite=true;
                    gameContainer.texte="Winner\n Keep going?";
                    header.foco=false;
                }
                if(!gamer.gameStatus())
                {
                    gameContainer.visibilite=true;
                    gameContainer.texte="End of Game";
                    header.foco=false;

                }
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
                gameContainer.visibilite=true;
                gameContainer.fontSize=20;
                gameContainer.texte="Developped by: \Francesco Zanoli\nMilter Shiniti Pesce";

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

        Score {
            id: score
            x: 217
            y: 21
            width: 118
            height: 67
            name: "Score"
            value: gamer.vScore
        }

        Score {
            id: bestScore
            x: 360
            y: 21
            width: 117
            height: 68
            name: "Best score"
            value: gamer.vBestScore
        }
    }

    GridBox {
        id: grid
        height: 450
        anchors.topMargin: 216
        width: 450
        anchors.rightMargin: 21
        anchors.bottomMargin: 27
        anchors.leftMargin: 21
        col: gamer.getTaille
        row: gamer.getTaille
        objectName: "grid"
    }

    GameContainer {
        id: gameContainer
        x: 34
        y: 228
        anchors.leftMargin: -177
        visibilite: false
        texte: "Game Over"
        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if (parent.texte=="End of Game")
                    return;
                parent.fontSize=51;
                parent.visibilite=false;
                header.foco=true;
                if (gamer.getMaxValue() == 2048)
                    gamer.keepWin();
            }
        }


    }


}






