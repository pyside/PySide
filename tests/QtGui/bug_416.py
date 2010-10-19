#!/usr/bin/python

import unittest
from helper import TimedQApplication
from PySide.QtCore import QSignalTransition, QState, Qt, QStateMachine
from PySide.QtGui import QCheckBox

class CheckedTransition(QSignalTransition):
    def __init__(self, check):
        QSignalTransition.__init__(self, check.stateChanged[int])
        self.eventTested = False

    def eventTest(self, event):
        self.eventTested = True
        if not QSignalTransition.eventTest(self, event):
            return False
        return event.arguments()[0] == Qt.Checked

class TestBug(TimedQApplication):
    def testCase(self):
        check = QCheckBox()
        check.setTristate(True)

        s1 = QState()
        s2 = QState()

        t1 = CheckedTransition(check)
        t1.setTargetState(s2)
        s1.addTransition(t1)

        machine = QStateMachine()
        machine.addState(s1)
        machine.addState(s2)
        machine.setInitialState(s1)
        machine.start()

        check.stateChanged[int].emit(1)
        check.show()
        self.app.exec_()
        self.assert_(t1.eventTested)

if __name__ == '__main__':
    unittest.main()
