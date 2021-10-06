import QtQuick 2.0
import fieldModel 1.0
import QtQuick.Layouts 1.13

Rectangle {
    property var sessionModel
    property var modelForField: sessionModel.model
    property alias canvas: canvas

    id: root
    visible: true
    Canvas{
        id: canvas
        z: gridview.z + 10
        anchors.fill: parent

        onPaint: {
            if(act == 0){
                drawLines();
                repaintAreas();
            }
            else if(act == 1){
                clear_canvas();
                drawLines();
                var areaNumber = modelForField.areasCount;
                repaintAreas();
                act = 0;
                modelForField.changePlayer();
            }
        }

        property int act: 0

        GridView{
            id: gridview

            z: -1
            anchors.fill: parent
            cellHeight: canvas.height / gridview.model.rows
            cellWidth: canvas.width / gridview.model.columns
            model: modelForField

            delegate: Item{
                id: itemdelegate
                height: gridview.cellHeight
                width: gridview.cellWidth

                Cell{
                    id: cell
                    anchors.fill: parent
                    property int index: model.index
                    property int occupiedByPlayer: model.edit
                    property int isClickable: model.display


                    MouseArea{
                        id: mousearea
                        anchors.fill: parent
                        onClicked: {
                            if(cell.occupiedByPlayer != -1 || !cell.isClickable) return;
                            cell.occupiedByPlayer = sessionmodel.player;
                            drawPointRequest(cell.occupiedByPlayer);
                            canvas.pointSet(cell.index, cell.occupiedByPlayer);
                        }

//                        signal draw()
//                        onDraw:{
//                            console.log("DRAW");
//                            drawPointRequest();
//                        }

                        function drawPointRequest(player)
                        {
//                            cell.occupiedByPlayer = sessionmodel.player;
                            if(player !== -1)
                                cell.drawingcanvas.drawPoint(sessionmodel.playerColor(player));
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
            for(var i = 0; i < modelForField.areasCount; ++i)
            {
                var coordsOfArea = modelForField.getAreaForPaint(i);
                var areaOwner = modelForField.getAreaOwner(i);
                if(areaOwner === -1) return;
                drawOccupiedArea(coordsOfArea, areaOwner);
            }
        }

        function pointSet(index, player)
        {
            fieldmodel.dfsStart(index, player);
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
