#!/usr/bin/python

import unittest
from testbinding import TestObject
from PySide.QtGui import QApplication

class QApplicationInstance(unittest.TestCase):

    def appDestroyed(self):
        sefl.assert_(False)

    def testInstanceObject(self):
        TestObject.createApp()
        app1 = QApplication.instance()
        app2 = QApplication.instance()
        app1.setObjectName("MyApp")
        self.assertEqual(app1, app2)
        self.assertEqual(app2.objectName(), app1.objectName())
        app1.destroyed.connect(self.appDestroyed)

if __name__ == '__main__':
    unittest.main()

