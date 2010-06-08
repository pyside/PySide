#!/usr/bin/env python

'''Using self.connect(signal, method)'''

import unittest

from PySide.QtCore import QObject, SIGNAL, SLOT
from PySide.QtGui import QPushButton, QWidget

from helper import UsesQApplication


class SelfConnect(UsesQApplication):

    def testButtonClickClose(self):
        button = QPushButton()
        button.connect(button, SIGNAL('clicked()'), SLOT('close()'))

        button.show()
        self.assert_(button.isVisible())
        button.click()
        self.assert_(not button.isVisible())

    def testWindowButtonClickClose(self):
        button = QPushButton()
        window = QWidget()
        window.connect(button, SIGNAL('clicked()'), SLOT('close()'))

        window.show()
        self.assert_(window.isVisible())
        button.click()
        self.assert_(not window.isVisible())



if __name__ == '__main__':
    unittest.main()
