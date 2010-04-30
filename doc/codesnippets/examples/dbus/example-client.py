#!/usr/bin/env python
# -*- coding: utf-8 -*-

# DBUS Client using PySide integration

import sys
from traceback import print_exc

# import python dbus module
import dbus
# import python dbus GLib mainloop support
import dbus.mainloop.glib
# import QtCore
from PySide.QtCore import *

# signal handler
def button_clicked():
    print "button clicked"

# main function
if __name__ == '__main__':

    # Enable glib main loop support
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    # Get the session bus
    bus = dbus.SessionBus()

    try:
        # Get the remote object
        remote_object = bus.get_object("com.example.SampleService",
                                       "/DBusWidget")
        # Get the remote interface for the remote object
        iface = dbus.Interface(remote_object, "com.example.SampleWidget")
    except dbus.DBusException:
        print_exc()
        sys.exit(1)

    # Start the application
    app = QCoreApplication([])

    # Call some methods of the remote interface
    iface.show()
    iface.setText("Emit signal")
    # connect the DBus signal clicked to the function button_clicked
    iface.connect_to_signal("clicked", button_clicked)
    iface.connect_to_signal("lastWindowClosed", app.quit)

    # enter in the main loop
    app.exec_()
