
import Qt 4.7

ListView {
    width: 300; height: 300
    delegate: Text { text: modelData }
    model: 3
}

