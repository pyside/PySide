
import unittest
from PySide import QtCore
import weakref

class LeakingSignal(unittest.TestCase):

    def testLeakingSignal(self):
        # Was segfaulting when the signal was garbage collected.
        class Emitter(QtCore.QObject):
            my_signal = QtCore.Signal(object)

        emitter = Emitter()

if __name__ == '__main__':
    unittest.main()
