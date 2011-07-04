import sys
import unittest

from PySide.QtCore import QFile
from PySide.QtGui import QTabWidget
from PySide.QtUiTools import QUiLoader

from helper import UsesQApplication
from helper import adjust_filename

class TestDestruction(UsesQApplication):
    def testBug909(self):
        fileName = QFile(adjust_filename('bug_909.ui', __file__))
        loader = QUiLoader()
        main_win = loader.load(fileName)
        self.assertEqual(sys.getrefcount(main_win), 2)
        fileName.close()

        tw = QTabWidget(main_win)
        main_win.setCentralWidget(tw)
        main_win.show()

if __name__ == '__main__':
    unittest.main()
