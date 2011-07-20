import Qt 4.7
import Example 1.0

Rectangle {
    width: 100
    height: 62

    MyClass {
        id: myClass
        urla: "http://www.pyside.org"
    }

    Text {
        id: name
        text: myClass.urla
    }
}
