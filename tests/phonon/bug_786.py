import unittest
from PySide.QtGui import *
from PySide.phonon import *


class TestBug786 (unittest.TestCase):

    def testIt(self):
        app = QApplication([])
        app.setApplicationName("PySide Phonon Unit Test")
        devices = Phonon.BackendCapabilities.availableAudioOutputDevices()
        if len(devices) > 1:
            if devices[0].index() != devices[0].index():
                self.assertNotEqual(devices[0], devices[1])
            self.assertEqual(devices[0], devices[0])

        effects = Phonon.BackendCapabilities.availableAudioEffects()
        if len(effects) > 1:
            self.assertNotEqual(effects[0], effects[1])
            self.assertEqual(effects[0], effects[0])

if __name__ == '__main__':
    unittest.main()
