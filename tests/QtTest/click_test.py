
'''QtTest mouse click functionalities'''

import unittest

from PySide.QtCore import Qt, QObject
from PySide.QtGui import QPushButton, QLineEdit
from PySide.QtTest import QTest

from helper import UsesQApplication

class MouseClickTest(UsesQApplication):

    def testBasic(self):
        '''QTest.mouseClick with QCheckBox'''
        button = QPushButton()
        button.setCheckable(True)
        button.setChecked(False)

        QTest.mouseClick(button, Qt.LeftButton)
        self.assert_(button.isChecked())

        QTest.mouseClick(button, Qt.LeftButton)
        self.assertFalse(button.isChecked())


if __name__ == '__main__':
    unittest.main()
