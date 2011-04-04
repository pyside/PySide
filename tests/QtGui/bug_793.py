import unittest
import sys
from PySide.QtCore import QTimer
from PySide.QtGui import QWidget, QApplication

class TestW1(QWidget):
    def __init__(self, parent = None):
        super(TestW1, self).__init__(parent)
        TestW2(parent, self)

class TestW2(QWidget):
    def __init__(self, ancestor, parent = None):
        super(TestW2, self).__init__(parent)
        self.ancestor_ref = ancestor

class Test(QWidget):
    def __init__(self):
        super(Test, self).__init__()
        TestW1(self)

class TestQApplicationDestrcutor(unittest.TestCase):
    def testDestructor(self):
        w = Test()
        w.show()
        QTimer.singleShot(0, w.close)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    unittest.main()
    sys.exit(app.exec_())
