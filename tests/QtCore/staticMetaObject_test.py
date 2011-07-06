import unittest

from PySide.QtCore import QObject, Slot, QMetaObject

class MyObject(QObject):
    @Slot(int, str)
    def slot1(self, a, b):
        pass

class testAttribute(unittest.TestCase):
    def testBug896(self):
        mo = MyObject.staticMetaObject
        self.assertTrue(isinstance(mo, QMetaObject))
        self.assertEqual(mo.className(), 'MyObject')
        self.assertTrue(mo.indexOfSlot('slot1(int,QString)') > -1)

    def testDuplicateSlot(self):
        mo = MyObject.staticMetaObject
        self.assertEqual(mo.indexOfSignal('destroyed(void)'), -1)
        self.assertTrue(mo.indexOfSignal('destroyed()') > -1)

if __name__ == '__main__':
    unittest.main()
