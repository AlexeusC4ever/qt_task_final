import QtQuick 2.0
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.12

Rectangle {
    id: root
    property var modelForTable
    property var fieldmodel

    ListView{
        id: listview
        height: 0.6 * parent.height
        width: parent.width
//        anchors.fill: parent
        x: 10
        y: 10
        model: modelForTable
        delegate: Item{
//            width: parent.width
            height: 20
            Text{
                color: model.decoration
                text: model.display + ":  " + model.edit
            }
        }

    }
    Rectangle{
        id: menu
        width: parent.width
        height: 0.4 * parent.height
        anchors{
            top: listview.bottom
            left: parent.left
        }
        Button{
            id: saveButton
            anchors.top: menu.top
            width: menu.width
            height: parent.height * 0.5
            MouseArea{
                anchors.fill: parent
                height: parent.height * 0.5
                Text{
                    text: "СОХРАНИТЬ ИГРУ"
                }
                onClicked:{
                    console.log("SAVe");
                    modelForTable.saveGameRequest("save");
                }
            }
        }
        Button{
            id: loadButton
            anchors.top: saveButton.bottom
            width: menu.width
            height: parent.height * 0.5
            MouseArea{
                anchors.fill: parent
                height: parent.height * 0.5
                Text{
                    text: "ЗАГРУЗИТЬ ИГРУ"
                }
                onClicked:{
                    console.log("LOAD");
                    modelForTable.loadGameRequest("save");
                }
            }
        }
    }
}
