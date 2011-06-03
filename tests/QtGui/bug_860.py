
import sys
import unittest

from PySide.QtCore import QSignalMapper
from PySide.QtGui import QCheckBox

from helper import UsesQApplication

class MultipleSlotTest(UsesQApplication):
    def cb_changed(self, i):
        self._changed = True

    def cb_changedVoid(self):
        self._changed = True

    def testSignalMapper(self):
        checkboxMapper = QSignalMapper()
        box = QCheckBox('check me')
        box.stateChanged.connect(checkboxMapper.map)

        checkboxMapper.setMapping(box, box.text())
        checkboxMapper.mapped[str].connect(self.cb_changed)
        self._changed = False
        box.setChecked(True)
        self.assert_(self._changed)

    def testSimpleSignal(self):
        box = QCheckBox('check me')
        box.stateChanged[int].connect(self.cb_changedVoid)
        self._changed = False
        box.setChecked(True)
        self.assert_(self._changed)

if __name__ == '__main__':
    unittest.main()
