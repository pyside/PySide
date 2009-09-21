
import unittest

from PySide.QtGui import QTabWidget
from helper import TimedQApplication

class RemoveTabMethod(TimedQApplication):
    def setUp(self):
        TimedQApplication.setUp(self)
        self.tab = QTabWidget()

    def tearDown(self):
        del self.tab
        TimedQApplication.tearDown(self)


    def testRemoveTabPresence(self):
        self.assert_(getattr(self.tab, 'removeTab'))

if __name__ == '__main__':
    unittest.main()
