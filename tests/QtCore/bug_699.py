import unittest
from PySide.QtCore import *

class TestBug699 (unittest.TestCase):

    def defClass(self):
        class Foo (QObject):
            def foo(self):
                pass

            prop = Property(foo, foo)

    def testIt(self):
        self.assertRaises(TypeError, self.defClass)

if __name__ == '__main__':
    unittest.main()
