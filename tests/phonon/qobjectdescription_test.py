import unittest

from PySide.QtCore import *
from PySide import phonon

from helper import UsesQCoreApplication

class CapabilitiesTest(UsesQCoreApplication):
    def testFromIndex(self):
        devices = phonon.Phonon.BackendCapabilities.availableAudioOutputDevices()
        for device in devices:
            self.assert_(isinstance(device, phonon.Phonon.AudioOutputDevice))
            other = phonon.Phonon.AudioOutputDevice.fromIndex(device.index())
            self.assertEqual(device.name(), other.name())
            self.assertEqual(device.index(), other.index())

if __name__ == '__main__':
    unittest.main()
