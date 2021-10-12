import QtQuick 2.0
import cellItem 1.0


Rectangle
{
    id: cell
    property alias drawingcanvas: drawingCanvas
    property var color;
    Canvas{
        id: drawingCanvas

        anchors.fill: parent
        onPaint: {
            if(!color) return;
            var ctx = getContext("2d")
            var radius = cell.height * 0.1;
            context.beginPath();
            context.arc(cell.width / 2, cell.height / 2, radius, 0, 2 * Math.PI, false);

            context.fillStyle = color;

            context.fill();
            context.stroke();
            requestPaint();
        }

        function drawPoint(playerColor){
            color = playerColor;
//            console.log(color);
            requestPaint();
        }
    }
}
