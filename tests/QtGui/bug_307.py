
import unittest
import colorsys

from PySide.QtCore import SIGNAL
from PySide.QtGui import QPushButton, QApplication


class Test (QApplication) :
    def __init__(self, argv) :
        super(Test, self).__init__(argv)
        self._called = False
        
    def called(self):
        self._called = True        


class QApplicationSignalsTest(unittest.TestCase):
    def testQuit(self):
        app = Test([])
        button = QPushButton("BUTTON")
        app.connect(button, SIGNAL("clicked()"), app.called)
        button.click()
        self.assert_(app._called)
        
if __name__ == '__main__':
    unittest.main()
