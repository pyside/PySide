
import os
import unittest
from PySide.phonon import Phonon
from helper import UsesQCoreApplication

sample_file = os.path.join(os.path.dirname(__file__), 'tone.wav')

def checkBackendCapabilities(func):
    def function(self, *args, **kw):
        if Phonon.BackendCapabilities.isMimeTypeAvailable('audio/x-wav'):
            func(self, *args, **kw)
        else:
            print('Wav format not supported! Playback test skipped!')
    return function


class TestSimplePlaying(UsesQCoreApplication):
    def setUp(self):
        super(TestSimplePlaying, self).setUp()
        self.app.setApplicationName('Dummy')
        self.source = Phonon.MediaSource(sample_file)
        self.media = Phonon.MediaObject()
        self.media.setCurrentSource(self.source)

        self.media.finished.connect(self.app.quit)
        self.called = False

        # prevent locking with:
        # request to play a stream, but no valid audio ...
        self.output = Phonon.AudioOutput()
        self.path = Phonon.createPath(self.media, self.output)

    def tearDown(self):
        super(TestSimplePlaying, self).tearDown()
        del self.path
        del self.output
        del self.media
        del self.source

    @checkBackendCapabilities
    def testFinishedSignal(self):
        # Should pass if finished() is called
        self.media.play()
        self.app.exec_()

    def testMediaSource(self):
        self.assertEqual(self.media.currentSource(), self.source)

    def testPathCreation(self):
        # FIXME Both functions below are not exported by PyQt4
        self.assertEqual(self.path.sink(), self.output)
        self.assertEqual(self.path.source(), self.media)

    def state_cb(self, newState, OldState):
        self.called = True

    @checkBackendCapabilities
    def testStateChanged(self):
        self.media.stateChanged['Phonon::State', 'Phonon::State'].connect(self.state_cb)
        self.media.play()
        self.app.exec_()
        self.assertTrue(self.called)


if __name__ == '__main__':
    unittest.main()

