# -*- coding: utf-8 -*-
import unittest
from PySide.QtCore import *


class SignalPrimitiveTypeTest(unittest.TestCase):

    def signalValueChanged(self, v):
        self.called = True
        self._app.quit()

    def createTimeLine(self):
        self.called = False
        tl = QTimeLine(10000)
        QObject.connect(tl, SIGNAL("valueChanged(qreal)"), self.signalValueChanged)
        return tl

    def testTimeLine(self):
        self._valueChangedCount = 0
        self._app = QCoreApplication([])
        tl = self.createTimeLine()
        tl.start()
        self._app.exec_()
        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()


