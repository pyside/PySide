''' Unit test for BUG #1041 '''

from PySide import QtCore, QtGui
import unittest
import re

gotDesiredError = False

def messageHandler(messageType, s):
    if re.match(".*unregister timer.*", s):
        global gotDesiredError
        gotDesiredError = True

class QTreeStuffTestCase(unittest.TestCase):
    def testQTreeWidget(self):
        ret = QtGui.QTreeWidget()
        del ret

        global gotDesiredError
        self.assertFalse(gotDesiredError)

    def testQTreeView(self):
        ret = QtGui.QTreeView()
        del ret

        global gotDesiredError
        self.assertFalse(gotDesiredError)

if __name__ == "__main__":
    app = QtGui.QApplication([])
    QtCore.qInstallMsgHandler(messageHandler)
    unittest.main()
