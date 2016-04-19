import QtQuick 2.5


Rectangle {
    property int col: 4
    property int row: 4
    radius: 9;

    anchors {
        right: parent.right; rightMargin: 5
        left: parent.left; leftMargin: 5
        bottom: parent.bottom; bottomMargin: 5
        top: parent.top; topMargin: 150
    }
    color: "#bbada0"

    Grid {
        id: grid
        anchors {
            right: parent.right; rightMargin: 5
            left: parent.left; leftMargin: 5
            bottom: parent.bottom; bottomMargin: 5
            top: parent.top; topMargin: 5
        }
        columns: col;
        rows: row;
        Repeater {
            model: grid.columns * grid.rows;

            Rectangle {
                width: grid.width / grid.columns;
                height: grid.height / grid.rows;
                color: "transparent";
                Rectangle {
                    color: "#ccc0b2"
                    radius: 9*4/col;
                    anchors {
                        right: parent.right; rightMargin: 3
                        left: parent.left; leftMargin: 3
                        bottom: parent.bottom; bottomMargin: 3
                        top: parent.top; topMargin: 3
                    }
                }
            }
        }
    }

    Grid{
        id:containerBox
        anchors.fill: parent
        columns: 4
        rows:4
    }
}
