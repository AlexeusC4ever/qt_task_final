import QtQuick 2.0
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.12

Rectangle {
    id: root

    ListView{
        id: listview
        height: 0.6 * parent.height
        width: parent.width
        x: 10
        y: 10
        model: sessionModel
        delegate: Item{
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
            height: parent.height / 4 - 3
            MouseArea{
                anchors.fill: parent
                Text{
                    anchors.centerIn: parent
                    text: qsTr("СОХРАНИТЬ ИГРУ")
                }
                onClicked:{
                    console.log("SAVE");
                    sessionModel.saveModel("save");
                }
            }
        }
        Button{
            id: loadButton
            anchors.top: saveButton.bottom
            width: menu.width
            height: saveButton.height
            MouseArea{
                anchors.fill: parent
                Text{
                    anchors.centerIn: parent
                    text: qsTr("ЗАГРУЗИТЬ ИГРУ")
                }
                onClicked:{
                    console.log("LOAD");
                    sessionModel.loadModel("save");
                }
            }
        }
        Button{
            id: networkButton
            anchors.top: loadButton.bottom
            width: menu.width
            height: saveButton.height
            MouseArea{
                anchors.fill: parent
                Text{
                    anchors.centerIn: parent
                    text: qsTr("ИГРАТЬ ПО СЕТИ")
                }
                onClicked:{
                    console.log("NET");
                    sessionModel.connectRequest();
                }
            }
        }
        Button{
            id: settingsButton
            anchors.top: networkButton.bottom
            width: menu.width
            height: saveButton.height
            MouseArea{
                anchors.fill: parent
                Text{
                    anchors.centerIn: parent
                    text: qsTr("НАСТРОЙКИ")
                }
                onClicked:{
                    console.log("NET");
                    sessionModel.showSettingsDialog();
                }
            }
        }
    }
}
