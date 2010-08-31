''' Test bug 324: http://bugs.openbossa.org/show_bug.cgi?id=324'''

import unittest
import sys
import signal
from PySide.QtCore import *
from PySide.QtGui import *

class QBug( QObject ):
    def __init__(self, parent = None):
        QObject.__init__(self, parent)

    def check(self):
        self.done.emit("abc")

    done = Signal(str)

class Bug324(unittest.TestCase):

    def on_done(self, val):
        self.value = val

    def testBug(self):
        app = QApplication([])
        bug = QBug()
        self.value = ''
        bug.done.connect(self.on_done)
        bug.check()
        self.assertEqual(self.value, 'abc')

if __name__ == '__main__':
    unittest.main()
