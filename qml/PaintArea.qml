import QtQuick 2.0
//import fieldModel 1.0
import QtQuick.Layouts 1.13

Rectangle {
//    property var sessionModel
//    property var modelForField/*: sessionModel.model*/
    property alias canvas: canvas


//    signal update()
//    onUpdate:{
//        console.log("ONUPDATE");
////        gridview.model.reset();
////        gridview.modelUpdated();
//    }


    Connections{
        target: gridview.model
        function onChangePlayer() {
//            console.log("Player:", sessionModel.player);
//            sessionModel.nextPlayer();
//            console.log("Player:", sessionModel.player);
            paintarea.canvas.dfsWorking = false;
//            console.log("CONNECTED");
//            sessionModel.tryChangeModel(15, 15);
        }

        function onRepaintAllAreas() {
            canvas.act = 1;
            canvas.requestPaint();
        }

        function onRepaintAll() {
            sessionModel.model.modelReset();
        }

        function onDataChanged(index, index, role)
        {
//            console.log("datachanged", index, gridview.model.data(index, role));
//            gridview.model.setData(index, role);
//            if(role == Display)
//            var player = gridview.model.at(index).reset();
        }
    }

    Connections{
        target: sessionModel
        function onModelChanged() {
//            sessionModel.modelReset();
            winnerrect.z = -10;
            sessionModel.model.modelReset();
            gridview.update();
            canvas.clear_canvas();
            canvas.requestPaint();
            console.log(sessionModel.model);
        }

        function onReadyToMove() {
            canvas.dfsWorking = false;
        }

        function onSendWinner(winner, winnername)
        {
            wintext.winner = winnername;
            wintext.color = sessionModel.playerColor(winner);
            wintext.visible = true;
            winnerrect.z = gridview.z + 20
        }
    }

    Rectangle{
        id: winnerrect
        z: -10
        anchors.fill: parent
        visible: true
        Text{
            id: wintext
            visible: true
            anchors.centerIn: parent
            fontSizeMode: Text.Fit;
            minimumPixelSize: 10;
            font.pixelSize: 20
            property var winner
            text: "Winner: " + winner
        }
    }

    id: root
    visible: true
    Canvas{
        id: canvas
        z: gridview.z + 1
        anchors.fill: parent

        onPaint: {
            if(act == 0){
                drawLines();
                repaintAreas();
            }
            else if(act == 1){
                clear_canvas();
                drawLines();
                var areaNumber = sessionModel.model.areasCount;
                repaintAreas();
                act = 0;
//                if(dfsWorking)
//                sessionModel.model.changePlayer();
            }
        }

        property int act: 0
        property bool dfsWorking: false

        GridView{
            id: gridview
            z: -1
            anchors.fill: parent
            cellHeight: canvas.height / gridview.model.rows
            cellWidth: canvas.width / gridview.model.columns
            model: sessionModel.model

            delegate: Item{
                id: itemdelegate

//                function onDataChanged(){
//                    drawPointRequest(cell.occupiedByPlayer);
//                }

                height: gridview.cellHeight
                width: gridview.cellWidth

                Cell{
                    id: cell
                    anchors.fill: parent
                    property int index: model.index
                    property int occupiedByPlayer: model.edit
                    property int isClickable: model.display
                    drawingcanvas.z: canvas.z + 1000
                    MouseArea{
                        id: mousearea
                        anchors.fill: parent
                        onClicked: {
                            if(cell.occupiedByPlayer != -1 || !cell.isClickable || canvas.dfsWorking ||
                                    (sessionModel.model.onlineGame && !sessionModel.onlineMoveFlag))
                                return;
                            canvas.dfsWorking = true;
                            cell.occupiedByPlayer = sessionModel.player;
                            drawPointRequest(cell.occupiedByPlayer);
                            canvas.pointSet(cell.index, cell.occupiedByPlayer);
                        }

                        function drawPointRequest(player)
                        {
//                            cell.occupiedByPlayer = sessionmodel.player;

                            if(player !== -1)
                                cell.drawingcanvas.drawPoint(sessionModel.playerColor(player));
                        }

                    }
                }
                Component.onCompleted: {
                    mousearea.drawPointRequest(cell.occupiedByPlayer);
                }
            }
        }

        function repaintAreas()
        {
            for(var i = 0; i < gridview.model.areasCount; ++i)
            {
                var coordsOfArea =  gridview.model.getAreaForPaint(i);
                var areaOwner =  gridview.model.getAreaOwner(i);
                if(areaOwner === -1) return;
                drawOccupiedArea(coordsOfArea, areaOwner);
            }
        }

        function pointSet(index, player)
        {
             sessionModel.model.dfsStart(index, player);
        }

        function drawOccupiedArea(coords, player)
        {
            if (!coords.length) return
            var arrayOfCoords = coords;

            var color = sessionModel.playerColor(player);
            var areaColor = sessionModel.playerColorForArea(player);

            var width = gridview.cellWidth;
            var height = gridview.cellHeight;

            var ctx = getContext('2d');
            ctx.lineWidth = 2;

            ctx.strokeStyle = color;
            ctx.fillStyle =  areaColor;
//            console.log("DRAW", color, areaColor);
            ctx.beginPath();

            ctx.moveTo((arrayOfCoords[0].y + 1) * width - 0.5 * width,
                       (arrayOfCoords[0].x + 1) * height - 0.5 * height);

            for(let i = 0; i < arrayOfCoords.length; ++i)
            {
                let coord = arrayOfCoords[i];
                ctx.lineTo((coord.y + 1) * width - 0.5 * width,
                           (coord.x + 1) * height - 0.5 * height);
            }
            ctx.closePath();
            ctx.fill();
            ctx.stroke();

            canvas.act = 0;
        }


        function drawLines()
        {
            var ctx = getContext('2d')
            ctx.lineWidth = 1;
            ctx.strokeStyle = "black"
            ctx.beginPath()
            var cellwidth = root.width / gridview.model.columns
            var cellheight = root.height / gridview.model.rows

            for(var i = cellwidth / 2; i < canvas.width; i = i + cellwidth)
            {
                ctx.moveTo(i, 0)
                ctx.lineTo(i, canvas.height)
            }
            for(var j = cellheight / 2; j < canvas.height; j = j + cellheight)
            {
                ctx.moveTo(0, j)
                ctx.lineTo(canvas.width, j)
            }
            ctx.closePath()
            ctx.stroke()
        }

        function clear_canvas()
        {
            var ctx = getContext("2d");
            ctx.reset();
        }
    }
}
