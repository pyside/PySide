
import unittest

from PySide.QtCore import QString
from PySide import phonon

from helper import UsesQCoreApplication

class CapabilitiesTest(UsesQCoreApplication):
    def setUp(self):
        super(CapabilitiesTest, self).setUp()
        self.app.setApplicationName("Dummy")

    def tearDown(self):
        super(CapabilitiesTest, self).tearDown()


    def testExists(self):
        self.assert_(phonon.Phonon.BackendCapabilities)

    def testNotifierIdentity(self):
        # Notifier is a singleton
        self.assertEqual(phonon.Phonon.BackendCapabilities.notifier(),
                         phonon.Phonon.BackendCapabilities.notifier())

        self.assert_(phonon.Phonon.BackendCapabilities.notifier() is
                     phonon.Phonon.BackendCapabilities.notifier())

    def testDevices(self):
        # TODO Improve this test
        devices = phonon.Phonon.BackendCapabilities.availableAudioOutputDevices()
        for device in devices:
            self.assert_(isinstance(device, phonon.Phonon.AudioOutputDevice))

    def testMimeTypes(self):
        # TODO Improve this test
        mimeTypes = phonon.Phonon.BackendCapabilities.availableMimeTypes()
        for mime in mimeTypes:
            self.assert_(isinstance(mime, QString))

    def testAudioEffects(self):
        # TODO Improve this test
        effects = phonon.Phonon.BackendCapabilities.availableAudioEffects()
        for effect in effects:
            self.assert_(isinstance(effect, phonon.Phonon.EffectDescription))

if __name__ == '__main__':
    unittest.main()
