# -*- coding: utf-8 -*-

import unittest

from PySide.QtCore import *
from PySide.QtGui import *

class MyObject(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self._method_called = False

    @Slot()
    def on_button_clicked(self):
        self._method_called = True


class AutoConnectionTest(unittest.TestCase):

    def testConnection(self):
        app = QApplication([])

        win = MyObject()
        btn = QPushButton("click", win)
        btn.setObjectName("button")
        QMetaObject.connectSlotsByName(win)
        btn.click()
        self.assert_(win._method_called)

if __name__ == '__main__':
    unittest.main()
