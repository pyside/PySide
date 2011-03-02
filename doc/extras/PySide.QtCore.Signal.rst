.. module:: PySide.QtCore
.. _Signal:

Signal
******

Synopsis
--------

Functions
^^^^^^^^^

+---------------------------------------------------------------------------------------------+
|def :meth:`connect<Signal.connect>` (receiver)                                               |
+---------------------------------------------------------------------------------------------+
|def :meth:`disconnect<Signal.disconnect>` (receiver)                                         |
+---------------------------------------------------------------------------------------------+
|def :meth:`emit<Signal.disconnect>` (\*args)                                                 |
+---------------------------------------------------------------------------------------------+

Detailed Description
--------------------

    The :class:`~.Signal` class provides a way to declare and connect Qt signals in a pythonic way.

    PySide adopt PyQt's new signal and slot syntax as-is. The PySide implementation is functionally compatible with the PyQt 4.5 one, with the exceptions listed bellow.

    .. note:: Parts of the documentation bellow are from the `PyQt4 documentation <http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/pyqt4ref.html#new-style-signal-and-slot-support>`_ public available on the internet Copyright (c) 2010 Riverbank Computing Limited just modified to fit the PySide implementation.


Defining New Signals with QtCore.Signal()
-----------------------------------------

    PySide automatically defines signals for all Qt's built-in signals. New signals can be defined as class attributes using the QtCore.Signal() factory.

    QtCore.Signal() takes a number of type arguments that corresponds to the signature of the signal. Each type may be a Python type object or a string that is the name of a C++ type. Alternatively each argument could be a sequence of type arguments. In this case each sequence defines the signature of a different signal overload. The first overload will be the default.

    QtCore.Signal() takes an optional name keyword argument that is the name of the signal. If it is omitted then the name of the class attribute is used.

    The following example shows the definition of a number of new signals:

    ::

        from PySide import QtCore

        class Foo(QtCore.QObject):

            # This defines a signal called 'closed' that takes no arguments.
            closed = QtCore.Signal()

            # This defines a signal called 'rangeChanged' that takes two
            # integer arguments.
            range_changed = QtCore.Signal(int, int, name='rangeChanged')

            # This defines a signal called 'valueChanged' that has two overloads,
            # one that takes an integer argument and one that takes a QString
            # argument.
            valueChanged = QtCore.Signal((int, ), (unicode, ))

            # The following will create exactly the same overloaded signal as
            # above and demonstrates the use of C++ type names instead of Python
            # type objects, and lists instead of tuples.
            valueChanged = QtCore.Signal(['int'], ['unicode'])

    New signals should only be defined in sub-classes of QObject.

    New signals defined in this way will be automatically added to the class's QMetaObject. This means that they will appear in Qt Designer and can be introspected using the QMetaObject API.

Connecting, Disconnecting and Emitting Signals
----------------------------------------------

    Signals are connected and disconnected to slots using the :meth:`Signal.connect` and :meth:`Signal.disconnect` methods of a bound signal and emitted using the :meth:`Signal.emit` method.

    The following code demonstrates the definition, connection and emit of a signal without arguments:

    ::

        from PySide import QtCore

        class Foo(QtCore.QObject):
            # Define a new signal called 'trigger' that has no arguments.
            trigger = QtCore.Signal()

            def connect_and_emit_trigger(self):
                # Connect the trigger signal to a slot.
                self.trigger.connect(self.handle_trigger)

                # Emit the signal.
                self.trigger.emit()

            def handle_trigger(self):
                # Show that the slot has been called.
                print "trigger signal received"

    The following code demonstrates the connection of overloaded signals:

    ::

        from PySide import QtGui

        class Bar(QtGui.QComboBox):

            def connect_activated(self):
                # Avoid using default overloads, they are not safe and can change in the future.
                self.activated.connect(self.handle_int)

                # For non-default overloads we have to specify which we want to
                # connect.  In this case the one with the single string argument.
                # (Note that we could also explicitly specify the default if we
                # wanted to.)
                self.activated[str].connect(self.handle_string)

            def handle_int(self, index):
                print "activated signal passed integer", index

            def handle_string(self, text):
                print "activated signal passed string", text

Connecting Signals Using Keyword Arguments
------------------------------------------

    It is also possible to connect signals by passing a slot as a keyword argument corresponding to the name of the signal when creating an object. For example the following three fragments are equivalent:

    ::

        act = QtGui.QAction("Action", self)
        act.triggered.connect(self.on_triggered)

        act = QtGui.QAction("Action", self, triggered=self.on_triggered)


.. method:: Signal.connect(receiver[, type=Qt.AutoConnection])

    Create a connection between this signal and a `receiver`, the `receiver` can be a Python callable, a :class:`Slot` or a :class:`Signal`.

.. method:: Signal.disconnect(receiver)

    Disconnect this signal from a `receiver`, the `receiver` can be a Python callable, a :class:`Slot` or a :class:`Signal`.

.. method:: Signal.emit(*args)

    `args` is the optional sequence of arguments to pass to any connected slots.

