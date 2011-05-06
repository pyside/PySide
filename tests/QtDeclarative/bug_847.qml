
import Qt 4.7

Rectangle {
    width: 500
    height: 500
    color: 'red'

    property variant pythonObject: undefined

    Text {
        anchors.centerIn: parent
        text: 'click me'
        color: 'white'
    }

    Timer {
        interval: 1; running: true;
        onTriggered: {
            if (pythonObject != undefined) {
                pythonObject.blubb(42, 84)
            }
        }
    }
}

