import QtQuick 2.0
import fieldModel 1.0
import QtQuick.Layouts 1.13

Rectangle {
    property var sessionModel
    property var modelForField: sessionModel.model
    property alias canvas: canvas
//    property alias player1color: player1color
//    property alias player2color: player2color

    id: root
    visible: true
    Canvas{
        id: canvas
        z: gridview.z + 10
        anchors.fill: parent

        onPaint: {
            if(act == 0){
                drawLines();
//                repaintAreas();
            }
            else if(act == 1){
                var areaNumber = modelForField.areasCount - 1;
                var coords = modelForField.coords;

                drawOccupiedArea(coords);
                sessionmodel.nextPlayer();
            }
        }

        property int act: 0
        property var player1color
        property var player2color

        GridView{
            id: gridview
            z: -1
            anchors.fill: parent
            cellHeight: canvas.height / gridview.model.rows
            cellWidth: canvas.width / gridview.model.columns
            model: modelForField

            delegate: Item{
                height: gridview.cellHeight
                width: gridview.cellWidth
                Cell{
                    id: cell
                    anchors.fill: parent
                    property int index: model.index
                    property int occupiedByPlayer: model.edit
                    property int isClickable: model.display
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            if(cell.occupiedByPlayer != -1 || !cell.isClickable) return;
                            cell.occupiedByPlayer = sessionmodel.player;
                            cell.drawingcanvas.drawPoint(sessionmodel.playerColor);
                            canvas.pointSet(cell.index, cell.occupiedByPlayer);
                        }
                    }
                }
            }
        }

        function repaintAreas()
        {
            for(var i = 0; i < modelForField.areasCount; ++i)
            {
                var coordsOfArea = modelForField.getAreaForPaint(i);
                drawOccupiedArea(coordsOfArea);
            }
        }

        function pointSet(index, player)
        {
//            console.log(index, player);
            fieldmodel.dfsStart(index, player);
//            fieldmodel.modelReset()
        }

        function drawOccupiedArea(coords)
        {
            if (!coords.length) return
            var arrayOfCoords = coords;
//            console.log(arrayOfCoords)

            var width = gridview.cellWidth;
            var height = gridview.cellHeight;

            var ctx = getContext('2d');
            ctx.lineWidth = 2;
            ctx.strokeStyle = sessionmodel.playerColor;

            var colorForArea = sessionmodel.playerColorForArea;

            ctx.fillStyle =  colorForArea;
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
    }
}
