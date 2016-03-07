import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 300
    height: 350
    title: qsTr("2048")


    MainForm {
        anchors.fill: parent
    }
}
