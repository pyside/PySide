
import unittest

from PySide.QtGui import *
from helper import TimedQApplication

def makeBug643(tab):
    button = QPushButton('Foo')
    tab.insertTab(0, button, 'Foo')

class RemoveTabMethod(TimedQApplication):
    def setUp(self):
        TimedQApplication.setUp(self)
        self.tab = QTabWidget()

    def tearDown(self):
        del self.tab
        TimedQApplication.tearDown(self)


    def testRemoveTabPresence(self):
        self.assert_(getattr(self.tab, 'removeTab'))

    def testInsertTab(self):
        makeBug643(self.tab)
        self.assertEqual(self.tab.count(), 1)

if __name__ == '__main__':
    unittest.main()
