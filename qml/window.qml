import QtQuick 2.0
import QtQuick.Controls 2.15


ApplicationWindow{
    id: mainWindow
    height: 500
    width: 700
    visible: true

    PaintArea{
        id: paintarea
        height: mainWindow.height
        width: mainWindow.width * 0.7
    }

    Session{
        id: session
        height: parent.height
        width: mainWindow.width * 0.3
        anchors.left: paintarea.right
        anchors.top: mainWindow.top
        border.width: 1
    }

}
