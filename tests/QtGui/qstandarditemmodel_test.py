import unittest

from PySide.QtGui import *
from PySide.QtCore import *

from helper import UsesQApplication

class QStandardItemModelTest(UsesQApplication):

    def setUp(self):
       super(QStandardItemModelTest, self).setUp()
       self.window = QWidget()
       self.model = QStandardItemModel(0, 3, self.window)

    def tearDown(self):
       del self.window
       del self.model
       super(QStandardItemModelTest, self).tearDown()

    def testInsertRow(self):
        # bug #227
        self.model.insertRow(0)

if __name__ == '__main__':
    unittest.main()

