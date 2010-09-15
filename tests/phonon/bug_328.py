#!/usr/bin/python

from PySide import QtCore, QtGui
from PySide.phonon import Phonon
import unittest

class TestBug(unittest.TestCase):
    def myCB(self):
        pass

    def testForNotifierSignals(self):
        # this test only check if the signals are present
        notifier = Phonon.BackendCapabilities.Notifier()
        notifier.capabilitiesChanged.connect(self.myCB)
        notifier.availableAudioOutputDevicesChanged.connect(self.myCB)

        self.assert_(True)

