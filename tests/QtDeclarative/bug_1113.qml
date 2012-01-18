import QtQuick 1.1
import Test 1.0

ListView {
    width: 400; height: 240;

    model: TestModel {
    }

    delegate: Item {
        height: 32
        width: parent.width
        Text {
            text: model.display
        }
    }
}
