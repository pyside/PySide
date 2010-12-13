
import unittest

from PySide.QtCore import QObject
from PySide.QtGui import QInputDialog

from helper import UsesQApplication

class DynamicSignalTest(UsesQApplication):

    def cb(self, obj):
        self._called = True

    def testQDialog(self):
        dlg = QInputDialog()
        dlg.setInputMode(QInputDialog.TextInput)
        lst = dlg.children()
        self.assert_(len(lst))
        obj = lst[0]
        self._called = False
        obj.destroyed[QObject].connect(self.cb)
        obj = None
        del dlg
        self.assert_(self._called)


if __name__ == '__main__':
    unittest.main()
