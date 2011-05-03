from PySide.QtGui import QApplication, QLabel, QMacStyle
from PySide.QtCore import QObject

import unittest

from helper import UsesQApplication

class QMacStyleTest(UsesQApplication):
    def testWidgetStyle(self):
        w = QLabel('Hello')
        self.assertTrue(isinstance(w.style(), QMacStyle))

if __name__ == '__main__':
    unittest.main()
