import QtQuick 2.0
import QtQuick.Controls 2.0
import sessionModel 1.0
import fieldModel 1.0


ApplicationWindow{
    id: mainWindow
    height: 500
    width: 500
    visible: true


    SessionModel{
        id: sessionmodel
        onSendWinner:{

        }

        onModelChanged: {
            console.log("RESET");
            modelReset();
            model.modelReset();
//            paintarea.gridview.draw();
        }

//        Connections {
//            target: fieldmodel
//            onModelReset:
//        }

        model: FieldModel{
            id: fieldmodel
            onChangePlayer: {
                  sessionmodel.nextPlayer();
//                paintarea.canvas.act = 1;
//                paintarea.canvas.requestPaint();
            }
            onRepaintAllAreas: {
//                paintarea.canvas.repaintAreas();
                paintarea.canvas.act = 1;
                paintarea.canvas.requestPaint();
            }
        }
    }

    PaintArea{
        id: paintarea
        sessionModel: sessionmodel
        height: mainWindow.height
        width: mainWindow.width * 0.7
    }


//    Rectangle {
//        id: session
//        height: parent.height
//        width: mainWindow.width * 0.3
//        anchors.left: paintarea.right
//        anchors.top: parent.top
//        border.width: 1
//        MouseArea{
//            anchors.fill: parent
//            onClicked: console.log("CLCIK")
//        }

//    }

    Session{
        id: session
        modelForTable: sessionmodel
        height: parent.height
        width: mainWindow.width * 0.3
        anchors.left: paintarea.right
        anchors.top: mainWindow.top
        border.width: 1
//        fieldmodel: paintarea.model
    }
}
