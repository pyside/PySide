import Qt 4.7

Rectangle {
    id: page
    width: 500; height: 200
    color: "lightgray"

    Rectangle {
        id: button
        width: 150; height: 40
        color: "darkgray"
        anchors.horizontalCenter: page.horizontalCenter
        y: 150
        MouseArea {
            id: buttonMouseArea
            objectName: "buttonMouseArea"
            anchors.fill: parent
        }
    }
}
