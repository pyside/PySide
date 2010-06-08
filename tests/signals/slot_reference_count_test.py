
''' Forced disconnection: Delete one end of the signal connection'''

import unittest
from sys import getrefcount

from PySide.QtCore import QObject, SIGNAL, SLOT

class Dummy(QObject):
    def dispatch(self):
        self.emit(SIGNAL('foo()'))

class PythonSignalRefCount(unittest.TestCase):

    def setUp(self):
        self.emitter = Dummy()

    def tearDown(self):
        self.emitter

    def testRefCount(self):
        def cb(*args):
            pass

        self.assertEqual(getrefcount(cb), 2)

        QObject.connect(self.emitter, SIGNAL('foo()'), cb)
        self.assertEqual(getrefcount(cb), 3)

        QObject.disconnect(self.emitter, SIGNAL('foo()'), cb)
        self.assertEqual(getrefcount(cb), 2)

class CppSignalRefCount(unittest.TestCase):

    def setUp(self):
        self.emitter = QObject()

    def tearDown(self):
        self.emitter

    def testRefCount(self):
        def cb(*args):
            pass

        self.assertEqual(getrefcount(cb), 2)

        QObject.connect(self.emitter, SIGNAL('destroyed()'), cb)
        self.assertEqual(getrefcount(cb), 3)

        QObject.disconnect(self.emitter, SIGNAL('destroyed()'), cb)
        self.assertEqual(getrefcount(cb), 2)

if __name__ == '__main__':
    unittest.main()
