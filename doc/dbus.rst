DBUS integration
****************

To get PySide and DBus working toghether you can use the glib mainloop integration already done in pydbus.

The example above show how to export Qt objects to python and emit an DBus signal when a Qtsignal is emited.  The code comments explains what you need to know about PySide and dbus, any doubts, see the python-dbus help.

DBUS Client
-----------

.. literalinclude:: ../examples/dbus/example-client.py


DBUS Server
-----------

.. literalinclude:: ../examples/dbus/example-server.py


Running the example
-------------------

Copy the client code to a file called ``example-client.py`` and the server to a file called ``example-server.py`` and type:

::

    $ python example-server.py &
    $ python example-client.py

A litle window should appear on screen. Click on the button to emit a Qt signal, this signal will be converted to a DBus signal that will be caught by our dbus client. That's all.
