
import unittest

from PySide.QtCore import QObject, SIGNAL

# Description of the problem
# After creating an PyObject that inherits from QObject, connecting it,
# deleting it and later creating another Python QObject-based object, this
# new object will point to the same memory position as the first one.

# Somehow the underlying QObject also points to the same position.

# In PyQt4, the connection works fine with the same memory behavior,
# so it looks like specific to SIP.

class Dummy(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)

class Joe(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)

class SegfaultCase(unittest.TestCase):
    """Test case for the segfault happening when parent() is called inside
    ProxyObject"""

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

    def testSegfault(self):
        """Regression: Segfault for qobjects in the same memory position."""
        obj = Dummy()
        QObject.connect(obj, SIGNAL('bar(int)'), self.callback)
        self.args = (33,)
        obj.emit(SIGNAL('bar(int)'), self.args[0])
        self.assert_(self.called)
        del obj

        obj = Joe()
        QObject.connect(obj, SIGNAL('bar(int)'), self.callback)
        self.args = (33,)
        obj.emit(SIGNAL('bar(int)'), self.args[0])
        self.assert_(self.called)


if __name__ == '__main__':
    unittest.main()

