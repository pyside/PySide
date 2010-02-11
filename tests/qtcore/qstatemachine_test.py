#!/usr/bin/python
import unittest
from PySide.QtCore import QObject, QState, QFinalState, SIGNAL, QCoreApplication, QTimer, QStateMachine, QSignalTransition, QVariant, QParallelAnimationGroup, QPropertyAnimation

from helper import UsesQCoreApplication

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
