New-style signal/slot
*********************
The new-style signal/slot was introduced by Riverbank on its PyQt v4.5. The main goal of this new-style is to provide a more pythonic syntax to the Python programmers. PySide uses `PSEP100 <http://www.pyside.org/docs/pseps/psep-0100.html>`_ as its implementation guideline.

Old way: SIGNAL() and SLOT()
----------------------------
Both QtCore.SIGNAL(...) and QtCore.SLOT(...) macros allow Python to interface with Qt mechanisms. This is the old way of using signals/slots.

The example below uses the well known *clicked* signal from a *QPushButton*. The *connect* method has a non python-friendly syntax. It is necessary to inform the object, its signal (via macro) and a slot to be connected to.

::

    ...

    def someFunc():
        print "someFunc has been called!"

    ...

    button = QtGui.QPushButton("Call someFunc")
    QtCore.QObject.connect(button, QtCore.SIGNAL('clicked()'), someFunc)

    ...


Next section shows how everything has changed to become more pythonic.

New way: signal() and slot()
----------------------------
The new-style uses a different syntax to create and to connect signals/slots. The previous example could be rewritten as:

::
    
    ...

    def someFunc():
        print "someFunc has been called!"

    ...

    clicked = QtCore.signal()

    button = QtGui.QPushButton("Call someFunc")
    button.clicked.connect(someFunc)

    ...


Using QtCore.signal()
---------------------
Signals can be defined using the *QtCore.signal()* class. Python types and C types can be passed as parameters to it. If you need to overload it just pass the types as tuples or lists.

Besides that it can receive also a named argument *name* that defines the signal name. If nothing is passed as *name* then the new signal will have the same name as the variable that it is being assigned to.

The section `Putting everything together`_ has a collection of examples that shows a bunch of situation using the *signal()* class.

**Note**: Signals should be defined only inside classes inheriting from QObject. This way the signal information is added to the class QMetaObject structure.


Using QtCore.slot()
-------------------
Slots are assigned and overloaded using the decorator *QtCore.slot()*. Again, to define a signature just pass the types like the *QtCore.signal()* class. Unlike the *signal()* class, to overload a function you don't pass every variation as tuple or list. Instead of that you have to define a new decorator for every different signature. The examples section below will make it clearer.

Another difference is about its keywords. *slot()* accepts a *name* and a *result*. The *result* keyword defines the type that will be returned and can be a C or Python type. The *name* behaves the same way as in *signal()*. If nothing is passed as *name* then the new slot will have the same name as the function that is being decorated.

Putting everything together
---------------------------
Nothing better than examples to show how to use the new-style. Here you can find some code covering a good range of cases, from basic connections to more complex situations.

- **Hello World example**: the basic example, showing how to connect a signal to a slot without any parameters.

::

    import sys
    from PySide import QtCore, QtGui

    # define a function that will be used as a slot
    def sayHello():
        print 'Hello world!'

    app = QtGui.QApplication(sys.argv)

    button = QtGui.QPushButton('Say hello!')

    # connect the clicked signal to the sayHello slot
    button.clicked.connect(sayHello)
    button.show()

    sys.exit(app.exec_())

- **Lets add some arguments**: this is a modified *Hello World* version. It adds some arguments to the slot and creates a new signal.

::

    import sys
    from PySide import QtCore

    # define a new slot that receives a QString and has
    # 'saySomeWords' as its name
    @QtCore.slot(QtCore.QString)
    def saySomeWords(words):
        print words

    class Communicate(QtCore.QObject):
        # create a new signal on the fly and name it 'speak'
        speak = QtCore.signal(QtCore.QString)

    someone = Communicate()
    # connect signal and slot
    someone.speak.connect(saySomeWords)
    # emit 'speak' signal
    someone.speak.emit("Hello everybody!")

- **Lets add some overloads**: a little more modification on the previous example now including overloads.

::

    import sys
    from PySide import QtCore

    # define a new slot that receives a C 'int' or a 'QString'
    # and has 'saySomething' as its name
    @QtCore.slot(int)
    @QtCore.slot(QtCore.QString)
    def saySomething(stuff):
        print stuff

    class Communicate(QtCore.QObject):
        # create two new signals on the fly: one will handle
        # int type, the other will handle QStrings
        speakNumber = QtCore.signal(int)
        speakWord = QtCore.signal(QtCore.QString)

    someone = Communicate()
    # connect signal and slot properly
    someone.speakNumber.connect(saySomething)
    someone.speakWord.connect(saySomething)
    # emit each 'speak' signal
    someone.speakNumber.emit(10)
    someone.speakWord.emit("Hello everybody!")


- **Lets complicate even more**: now with overloads and complicated connections and emissions.

::

    import sys
    from PySide import QtCore

    # define a new slot that receives an C 'int' or a 'QString'
    # and has 'saySomething' as its name
    @QtCore.slot(int)
    @QtCore.slot(QtCore.QString)
    def saySomething(stuff):
        print stuff

    class Communicate(QtCore.QObject):
        # create two new signals on the fly: one will handle
        # int type, the other will handle QStrings
        speak = QtCore.signal((int,), (QtCore.QString,))

    someone = Communicate()
    # connect signal and slot. As 'int' is the default
    # we have to inform the QString when connecting the
    # second signal
    someone.speak.connect(saySomething)
    someone.speak[QtCore.QString].connect(saySomething)

    # emit 'speak' signal with different arguments.
    # we have to inform the QString as int is the default
    someone.speak.emit(10)
    someone.speak[QtCore.QString].emit("Hello everybody!")


PyQt compatibility
------------------
PyQt uses a different naming convention to its new signal/slot functions. In order to convert any PyQt script that uses this new-style to run with PySide just use one the proposed modifications below:

::

    from PySide.QtCore import signal as pyqtSignal
    from PySide.QtCore import slot as pyqtSlot

or

::

    QtCore.pyqtSignal = QtCore.signal
    QtCore.pyqtSlot = QtCore.slot

This way any call to *pyqtSignal* or *pyqtSlot* will be translated to a *signal* or *slot* call.
