import QtQuick 2.0
import QtQuick.Controls 2.15
//import sessionModel 1.0
//import fieldModel 1.0


ApplicationWindow{
    id: mainWindow
    height: 500
    width: 500
    visible: true


//    sessionModel{
//        id: sessionmodel

//        property int networkConnect: 0

//        model: fieldModel

////        onSendWinner:{

////        }

//        Connections{
//            target: model
//            onChangePlayer: {
//                sessionmodel.nextPlayer();
//                paintarea.canvas.dfsWorking = false;
//                console.log("CHANGE");
//            }
//            onRepaintAllAreas: {
//                paintarea.canvas.act = 1;
//                paintarea.canvas.requestPaint();
//            }
//        }

//        onModelChanged: {
//            modelReset();
//            model.modelReset();


////            paintarea.sessionModel = sessionmodel;
////            paintarea.modelForField = sessionmodel.model;
//            paintarea.update();
//            console.log(sessionmodel.model);
//        }


////        model: FieldModel{
////            id: fieldmodel
////            onChangePlayer: {
////                sessionmodel.nextPlayer();
////                paintarea.canvas.dfsWorking = false;
////                console.log("CHANGE");
////            }
////            onRepaintAllAreas: {
////                paintarea.canvas.act = 1;
////                paintarea.canvas.requestPaint();
////            }
////        }
//    }

    PaintArea{
        id: paintarea
//        sessionModel: Session
//        modelForField: sessionmodel.model
        height: mainWindow.height
        width: mainWindow.width * 0.7
    }

    Session{
        id: session
//        modelForTable: Session
        height: parent.height
        width: mainWindow.width * 0.3
        anchors.left: paintarea.right
        anchors.top: mainWindow.top
        border.width: 1
    }

}
