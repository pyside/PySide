import unittest

from PySide.QtCore import QObject

class MyObject(QObject):
    pass

class MainTest(unittest.TestCase):
    def testInherits(self):
        o = MyObject()
        mo = o.metaObject()
        self.assertEqual(mo.className(), 'MyObject')
        self.assertTrue(o.inherits('MyObject'))

if __name__ == '__main__':
    unittest.main()
