import unittest

from PySide.QtCore import QObject

class MyBaseObject(QObject):
    def __init__(self, number):
        self.myMember = 'myMember' + number
        QObject.__init__(self)

class QObjectConstructorTest(unittest.TestCase):
    def testBug(self):
        for i in range(10):
            number = str(i)
            obj = MyBaseObject(number)
            self.assertEqual(obj.myMember, 'myMember' + number)

if __name__ == '__main__':
    unittest.main()
