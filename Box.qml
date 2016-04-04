import QtQuick 2.5

Item {

    property string valeur: "2"
    property int val_x
    property int val_y
    property bool animMoveEnable;
    property bool animResizeEnable;
    property bool visibilite: true;
    property int taille: 100;
    property int size: 100;

    Rectangle {
        id: rectangle1


        visible: visibilite
        width: size
        height: size
        x: val_x
        y: val_y
        color: "transparent"

        Rectangle{
            color: switch (valeur){
                   case "":
                       "#ccc0b2"
                       break;
                   case "2":
                       "#eee4da"
                       break;
                   case "4" :
                       "#ece0c8";
                       break;
                   case "8" :
                       "#f2b179";
                       break;
                   case "16" :
                       "#f59563";
                       break;
                   case "32" :
                       "#f57c5f";
                       break;
                   case "64" :
                       "#f95c3b";
                       break;
                   case "128" :
                       "#edce71";
                       break;
                   case "256" :
                       "#eecc61";
                       break;
                   case "512" :
                       "#ebc850";
                       break;
                   case "1024" :
                       "#edc53f";
                       break;
                   case "2048" :
                       "#eec22e";
                       break;
                   case "4096" :
                       "#3d3a33";
                       break;
                   case "8192" :
                       "#3d3a33";
                       break;
                   case "16384" :
                       "#3d3a33" ;
                       break;
                   default:
                       "#3d3a33"
                       break;
                   }
            radius: 9*taille/100;
            anchors.centerIn: parent
            width: taille
            height: taille

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: valeur == "2" || valeur == "4" ? "#786f66" : "#f7f8f0"
                text: valeur
                styleColor: "#786f66"
                style: Text.Outline
                font.bold: true
                font.family: "Tahoma"
                font.pixelSize: 45*size/100
            }

            Behavior on color {
                ColorAnimation {
                    duration: 300
                }
            }
        }


        Behavior on width {
            enabled: animResizeEnable;
            NumberAnimation {
                objectName: "wAni";
                duration: 1000;

            }
        }

        Behavior on height {
            enabled: animResizeEnable;

            NumberAnimation {
                objectName: "hAni";
                duration: 1000;

            }
        }

        Behavior on x {
            enabled: animMoveEnable
            objectName: "xmove"
            NumberAnimation {
                objectName: "xAni";
                duration: 200;

            }
        }

        Behavior on y {
            enabled: animMoveEnable
            objectName: "ymove"
            NumberAnimation {
                objectName: "yAni";
                duration: 200;

            }
        }
    }
}
