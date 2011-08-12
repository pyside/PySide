from PySide.QtUiTools import QUiLoader
import unittest

from helper import UsesQApplication
from helper import adjust_filename

class MyQUiLoader(QUiLoader):
    def __init__(self):
        super(MyQUiLoader, self).__init__()

    def createWidget(self, className, parent=None, name=""):
        return None

class BugTest(UsesQApplication):
    def testCase(self):
        loader = MyQUiLoader()
        self.assertRaises(RuntimeError, loader.load, adjust_filename('bug_965.ui', __file__))

if __name__ == '__main__':
    unittest.main()
