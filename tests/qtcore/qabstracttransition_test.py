#!/usr/bin/python
import unittest
from PySide.QtCore import QObject, QState, QFinalState, SIGNAL, QCoreApplication, QTimer, QStateMachine, QSignalTransition, QVariant, QParallelAnimationGroup

def addStates(transition):
    sx = QState()
    sy = QState()
    transition.setTargetStates([sx, sy])

def addAnimation(transition):
    animation = QParallelAnimationGroup()
    transition.addAnimation(animation)

class QAbstractTransitionTest(unittest.TestCase):

    def testBasic(self):
        app = QCoreApplication([])

        o = QObject()
        o.setProperty("text", QVariant("INdT"))

        machine = QStateMachine()
        s1 = QState()
        s1.assignProperty(o, "text", QVariant("Rocks"))

        s2 = QFinalState()
        t = s1.addTransition(o, SIGNAL("change()"), s2)

        self.assertEqual(t.targetStates(), [s2])

        addStates(t)
        self.assertEqual(len(t.targetStates()), 2)

        animation = QParallelAnimationGroup()
        t.addAnimation(animation)

        self.assertEqual(t.animations(), [animation])

        addAnimation(t)
        self.assertEqual(t.animations()[0].parent(), None)

        machine.addState(s1)
        machine.addState(s2)
        machine.setInitialState(s1)
        machine.start()

        QTimer.singleShot(100, app.quit)
        app.exec_()

if __name__ == '__main__':
    unittest.main()
