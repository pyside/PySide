''' unit test for BUG #1126 '''
''' see http://bugs.pyside.org/show_bug.cgi?id=1126 '''

from helper import UsesQApplication
import unittest
from PySide import QtCore, QtGui

class SignalInstanceDisconnTestCase(UsesQApplication):
    def testIt(self):
        w = QtGui.QWidget()
        w.deleteLater()

        def cb(*args):
            self.app.quit()

        w.destroyed.connect(cb)
        self.app.exec_()
        try:
            w.destroyed.disconnect(cb)
        except RuntimeError:
            pass

if __name__ == "__main__":
    unittest.main()
