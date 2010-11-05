import Qt 4.7

Rectangle {
    id: page

    function simpleFunction() {
        python.called = "simpleFunction"
    }

    function oneArgFunction(x) {
        python.called = "oneArgFunction"
        python.arg1 = x
    }

    function twoArgFunction(x, y) {
        python.called = "twoArgFunction"
        python.arg1 = x
        python.arg2 = y
    }

    function returnFunction() {
        python.called = "returnFunction"
        return 42
    }

}
