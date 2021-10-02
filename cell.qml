import QtQuick 2.0


Rectangle
{
    id: cell
    property alias drawingcanvas: drawingCanvas

    Canvas{
        id: drawingCanvas
        anchors.fill: parent

        function drawPoint(playerColor){
            var ctx = getContext("2d")
            var radius = cell.height * 0.1;
            context.beginPath();
            context.arc(cell.width / 2, cell.height / 2, radius, 0, 2 * Math.PI, false);

            context.fillStyle = playerColor;

            context.fill();
            context.stroke();
            requestPaint();
        }
    }
}
