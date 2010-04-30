#!/usr/bin/env python
# -*- coding: utf-8 -*-

# DBUS Server Example of use PySide with PyDBus library

import dbus
import dbus.service
import dbus.mainloop.glib
import random

from PySide.QtCore import *
from PySide.QtGui import QPushButton, QApplication

# The adaptor, MUST inherit dbus.service.Object
class DBusWidget(dbus.service.Object):
    def __init__(self, name, session):
        # export this object to dbus
        dbus.service.Object.__init__(self, name, session)

        # create a simple widget
        self.widget = QPushButton()
        self.widget.resize(200, 50)

        # To export a Qt signal as a DBus-signal, you need to connect it to a method in this class.
        # The method MUST have the signal annotation, so python-dbus will export it as a dbus-signal
        QObject.connect(self.widget, SIGNAL("clicked()"), self.clicked)
        QObject.connect(QApplication.instance(), SIGNAL("lastWindowClosed()"), self.lastWindowClosed)

    # You can export methods to dbus like you do in python-dbus.
    @dbus.service.method("com.example.SampleWidget", in_signature='', out_signature='')
    def show(self):
        self.widget.show()

    # Another method... now with a parameter
    @dbus.service.method("com.example.SampleWidget", in_signature='s', out_signature='')
    def setText(self, value):
        self.widget.setText(value)

    # Another one...
    @dbus.service.method("com.example.SampleWidget", in_signature='', out_signature='')
    def exit(self):
        qApp().quit()

    # A signal that will be exported to dbus
    @dbus.service.signal("com.example.SampleWidget", signature='')
    def clicked(self):
        pass

    # Another signal that will be exported to dbus
    @dbus.service.signal("com.example.SampleWidget", signature='')
    def lastWindowClosed(self):
        pass


if __name__ == '__main__':
    app = QApplication([])
    # Use qt/glib mainloop integration to get dbus mainloop working
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    # Export the service
    name = dbus.service.BusName("com.example.SampleService", session_bus)
    # Export the object
    widget = DBusWidget(session_bus, '/DBusWidget')

    print "Running example service."
    app.exec_()

