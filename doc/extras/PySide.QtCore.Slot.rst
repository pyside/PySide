.. module:: PySide.QtCore
.. _Slot:

Slot
****

Detailed Description
--------------------

    PySide adopt PyQt's new signal and slot syntax as-is. The PySide
    implementation is functionally compatible with the PyQt 4.5 one, with the
    exceptions listed bellow.

    PyQt's new signal and slot style utilizes method and decorator names
    specific to their implementation. These will be generalized according to
    the table below:

    =======  ======================  =============
    Module   PyQt factory function   PySide class
    =======  ======================  =============
    QtCore   pyqtSignal              Signal
    QtCore   pyqtSlot                Slot
    =======  ======================  =============

Q_INVOKABLE
-----------

    PySide doesn't offer something identical to Q_INVOKABLE macro of Qt, the
    reason is simple, PySide slots can have return values, so if you need to
    create a invokable method that returns some value, declare it as a slot,
    e.g.:

    ::

        class Foo(QObject):

            @Slot(result=int, float)
            def getFloatReturnInt(self, f):
                return int(f)
