#!/usr/bin/python
import unittest
from PySide.QtCore import QObject, QState, QFinalState, SIGNAL
from PySide.QtCore import QTimer, QStateMachine
from PySide.QtCore import QParallelAnimationGroup

from helper import UsesQCoreApplication


class StateMachineTest(unittest.TestCase):
    '''Check presence of State Machine classes'''

    def testBasic(self):
        '''State machine classes'''
        import PySide.QtCore
        PySide.QtCore.QSignalTransition
        PySide.QtCore.QPropertyAnimation



class QStateMachineTest(UsesQCoreApplication):

    def cb(self, *args):
        self.assertEqual(self.machine.defaultAnimations(), [self.anim])

    def testBasic(self):
        self.machine = QStateMachine()
        s1 = QState()
        s2 = QState()
        s3 = QFinalState()

        QObject.connect(self.machine, SIGNAL("started()"), self.cb)

        self.anim = QParallelAnimationGroup()

        self.machine.addState(s1)
        self.machine.addState(s2)
        self.machine.addState(s3)
        self.machine.setInitialState(s1)
        self.machine.addDefaultAnimation(self.anim)
        self.machine.start()

        QTimer.singleShot(100, self.app.quit)
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()
