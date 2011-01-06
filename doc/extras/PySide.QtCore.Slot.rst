.. module:: PySide.QtCore
.. _Slot:

Slot
****

Detailed Description
--------------------

    PySide adopt PyQt's new signal and slot syntax as-is. The PySide implementation is functionally compatible with the PyQt 4.5 one, with the exceptions listed bellow.

    .. note:: Parts of the documentation bellow are from the `PyQt4 documentation <http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/pyqt4ref.html#new-style-signal-and-slot-support>`_ public available on the internet Copyright (c) 2010 Riverbank Computing Limited just modified to fit the PySide implementation.

    Although PySide allows any Python callable to be used as a slot when connecting signals, it is sometimes necessary to explicitly mark a Python method as being a Qt slot and to provide a C++ signature for it. PySide provides the QtCore.Slot() function decorator to do this.

    All of the non-keyword arguments to the decorator are interpreted as the types of the corresponding C++ arguments. A type is either a Python type object or a string that specifies a C++ type. The decorator also takes two optional keywords arguments: name and result. name is the name of the slot that will be seen by C++. If ommitted the name of the Python method being decorated will be used. result is the type of the result and may also be a Python type object or a string that specifies a C++ type.

    For example:

    ::

        @QtCore.Slot()
        def foo(self):
            """ C++: void foo() """

        @QtCore.Slot(int, unicode)
        def foo(self, arg1, arg2):
            """ C++: void foo(int, QString) """

        @QtCore.Slot(int, name='bar')
        def foo(self, arg1):
            """ C++: void bar(int) """

        @QtCore.Slot(int, result=int)
        def foo(self, arg1):
            """ C++: int foo(int) """

        @QtCore.Slot(int, QtGui.QWidget)
        def foo(self, arg1):
            """ C++: int foo(int, QWidget*) """

    It is also possible to chain the decorators in order to define a Python method several times with different signatures.

    For example:

    ::

        @QtCore.Slot(int)
        @QtCore.Slot('QString')
        def valueChanged(self, value):
            """ Two slots will be defined in the QMetaObject. """

Connecting Slots By Name
------------------------

    PySide supports the QtCore.QMetaObject.connectSlotsByName() function that is most commonly used by pyside-uic generated Python code to automatically connect signals to slots that conform to a simple naming convention besides the QtCore.Slot decoration.

    For example the :class:`PySide.QtGui.QSpinBox` class has the following signals:

    ::

        void valueChanged(int i);
        void valueChanged(const QString& text);

    For example, if you were interested in the integer variant of the signal then your slot definition would look like the following:

    ::

        @QtCore.Slot(int)
        def on_spinbox_valueChanged(self, i):
            # i will be an integer.
            pass

    If you wanted to handle both variants of the signal, but with different Python methods, then your slot definitions might look like the following:

    ::

        @QtCore.Slot(int, name='on_spinbox_valueChanged')
        def spinbox_int_value(self, i):
            # i will be an integer.
            pass

        @QtCore.Slot(unicode, name='on_spinbox_valueChanged')
        def spinbox_qstring_value(self, s):
            # s will be a Python unicode object.
            pass

    The following shows an example using a button when you are not interested in the optional argument:

    ::

        @QtCore.Slot()
        def on_button_clicked(self):
            pass

