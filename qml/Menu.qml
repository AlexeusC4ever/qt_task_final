import QtQuick 2.0

Rectangle{
    anchors.centerIn: parent
    height: 30
    border.width: 1
    Text{
        text: "Начать игру"
    }
    MouseArea{
        anchors.fill: parent
        onClicked: startGame()
    }
}

