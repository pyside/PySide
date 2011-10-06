
import unittest
import py3kcompat as py3k

from PySide import phonon

from helper import UsesQCoreApplication

class CapabilitiesTest(UsesQCoreApplication):
    def setUp(self):
        super(CapabilitiesTest, self).setUp()
        self.app.setApplicationName("Dummy")

    def tearDown(self):
        super(CapabilitiesTest, self).tearDown()


    def testExists(self):
        self.assertTrue(phonon.Phonon.BackendCapabilities)

    def testNotifierIdentity(self):
        # Notifier is a singleton
        self.assertEqual(phonon.Phonon.BackendCapabilities.notifier(),
                         phonon.Phonon.BackendCapabilities.notifier())

        self.assertTrue(phonon.Phonon.BackendCapabilities.notifier() is
                     phonon.Phonon.BackendCapabilities.notifier())

    def testDevices(self):
        # TODO Improve this test
        devices = phonon.Phonon.BackendCapabilities.availableAudioOutputDevices()
        for device in devices:
            self.assertTrue(isinstance(device, phonon.Phonon.AudioOutputDevice))

    def testMimeTypes(self):
        # TODO Improve this test
        mimeTypes = phonon.Phonon.BackendCapabilities.availableMimeTypes()
        for mime in mimeTypes:
            self.assertTrue(isinstance(mime, py3k.unicode))

    def testAudioEffects(self):
        # TODO Improve this test
        effects = phonon.Phonon.BackendCapabilities.availableAudioEffects()
        for effect in effects:
            self.assertTrue(isinstance(effect, phonon.Phonon.EffectDescription))

if __name__ == '__main__':
    unittest.main()
