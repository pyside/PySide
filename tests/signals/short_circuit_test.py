
import unittest

from PySide.QtCore import QObject, SIGNAL, SLOT

class Dummy(QObject):
    """Dummy class used in this test."""
    def __init__(self, parent=None):
        QObject.__init__(self, parent)

class ShortCircuitSignals(unittest.TestCase):
    def setUp(self):
        self.called = False

    def tearDown(self):
        try:
            del self.args
        except:
            pass

    def callback(self, *args):
        if tuple(self.args) == args:
            self.called = True

    def testNoArgs(self):
        """Short circuit signal without arguments"""
        obj1 = Dummy()

        QObject.connect(obj1, SIGNAL('foo'), self.callback)
        self.args = tuple()
        obj1.emit(SIGNAL('foo'), *self.args)

        self.assert_(self.called)

    def testWithArgs(self):
        """Short circuit signal with integer arguments"""
        obj1 = Dummy()

        QObject.connect(obj1, SIGNAL('foo'), self.callback)
        self.args = (42,)
        obj1.emit(SIGNAL('foo'), *self.args)

        self.assert_(self.called)

    def testMultipleArgs(self):
        """Short circuit signal with multiple arguments"""
        obj1 = Dummy()

        QObject.connect(obj1, SIGNAL('foo'), self.callback)
        self.args = (42,33,'char')
        obj1.emit(SIGNAL('foo'), *self.args)

        self.assert_(self.called)

    def testComplexArgs(self):
        """Short circuit signal with complex arguments"""
        obj1 = Dummy()

        QObject.connect(obj1, SIGNAL('foo'), self.callback)
        self.args = (42, obj1)
        obj1.emit(SIGNAL('foo'), *self.args)

        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()
