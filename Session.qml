import QtQuick 2.0
import QtQuick.Layouts 1.13

Rectangle {
    property var modelForTable
    property var fieldmodel

    ListView{
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.topMargin: 10
        model: modelForTable
        delegate: Item{
            width: parent.width
            height: 20
            Text{
                color: model.decoration
                text: model.display + ":  " +  model.edit
            }
        }
        Component.onCompleted: {
            console.log();
        }

    }
}
