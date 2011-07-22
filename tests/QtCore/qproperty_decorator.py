import weakref
import unittest

from PySide.QtCore import QObject, Property

class MyObject(QObject):
    def __init__(self):
        QObject.__init__(self)
        self._value = None

    @Property(int)
    def value(self):
        return self._value

    @value.setter
    def valueSet(self, value):
        self._value = value


class PropertyTest(unittest.TestCase):
    def destroyCB(self, obj):
        self._obDestroyed = True

    def testDecorator(self):
        self._obDestroyed = False
        o = MyObject()
        weak = weakref.ref(o, self.destroyCB)
        o.value = 10
        self.assertEqual(o._value, 10)
        self.assertEqual(o.value, 10)
        del o
        self.assertTrue(self._obDestroyed)

if __name__ == '__main__':
    unittest.main()
