import unittest

from PySide.QtCore import QObject

class MyBaseObject(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self.setObjectName("PySide")

    def __del__(self):
        if self.objectName() != "PySide":
            raise NameError('Fail')

class CheckForEventsTypes(unittest.TestCase):
    def testDelObject(self):
        p = MyBaseObject()
        o = MyBaseObject(p)
        del o
        del p

if __name__ == '__main__':
    unittest.main()
