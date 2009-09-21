
import unittest

from PySide.QtCore import QObject, SIGNAL, Qt

class Dummy(QObject):
    """Dummy class used in this test."""
    def __init__(self, parent=None):
        QObject.__init__(self, parent)

class TestConnectionTypeSupport(unittest.TestCase):
    def callback(self, *args):
        if tuple(self.args) == args:
            self.called = True

    def testNoArgs(self):
        """Connect signal using a Qt.ConnectionType as argument"""
        obj1 = Dummy()

        QObject.connect(obj1, SIGNAL('foo'), self.callback, Qt.DirectConnection)
        self.args = tuple()
        obj1.emit(SIGNAL('foo'), *self.args)

        self.assert_(self.called)


if __name__ == '__main__':
    unittest.main()
