
import unittest

from PySide.QtCore import QObject, SIGNAL, SLOT

# Upstream version of segfault_test

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


    def testSameReference(self):
        """Example of how sip reuses an already used PyObject"""
        obj = Dummy()
        s1 = str(obj)
        del obj
        obj = Dummy()
        s2 = str(obj)
        self.assertEqual(s1, s2)

        obj2 = Dummy()
        s3 = str(obj2)
        self.assertNotEqual(s2, s3)


if __name__ == '__main__':
    unittest.main()

