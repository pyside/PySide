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

.. method:: Signal.connect(receiver[, type=Qt.AutoConnection])

    Create a connection between this signal and a `receiver`, the `receiver` can be a Python callable, a :class:`Slot` or a :class:`Signal`.

.. method:: Signal.disconnect(receiver)

    Disconnect this signal from a `receiver`, the `receiver` can be a Python callable, a :class:`Slot` or a :class:`Signal`.

.. method:: Signal.emit(*args)

    `args` is the arguments to pass to any connected slots, if any.

