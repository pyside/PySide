#!/usr/bin/python
import unittest
from sys import getrefcount
from PySide.QtCore import *

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
        o.setProperty("text", "INdT")

        machine = QStateMachine()
        s1 = QState()
        s1.assignProperty(o, "text", "Rocks")

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

    def testRefCountOfTargetState(self):
        transition = QEventTransition()
        state1 = QState()
        refcount1 = getrefcount(state1)

        transition.setTargetState(state1)

        self.assertEqual(transition.targetState(), state1)
        self.assertEqual(getrefcount(transition.targetState()), refcount1 + 1)

        state2 = QState()
        refcount2 = getrefcount(state2)

        transition.setTargetState(state2)

        self.assertEqual(transition.targetState(), state2)
        self.assertEqual(getrefcount(transition.targetState()), refcount2 + 1)
        self.assertEqual(getrefcount(state1), refcount1)

        del transition

        self.assertEqual(getrefcount(state2), refcount2)

    def testRefCountOfTargetStates(self):
        transition = QEventTransition()
        state1 = QState()
        state2 = QState()
        states = [state1, state2]
        refcount1 = getrefcount(state1)
        refcount2 = getrefcount(state2)

        transition.setTargetStates(states)

        self.assertEqual(transition.targetStates(), states)
        self.assertEqual(transition.targetState(), state1)
        self.assertEqual(getrefcount(transition.targetStates()[0]), refcount1 + 1)
        self.assertEqual(getrefcount(transition.targetStates()[1]), refcount2 + 1)

        del states
        del transition

        self.assertEqual(getrefcount(state1), refcount1 - 1)
        self.assertEqual(getrefcount(state2), refcount2 - 1)

    def testRefCountOfTargetStatesAfterSingleTargetState(self):
        transition = QEventTransition()
        state0 = QState()
        refcount0 = getrefcount(state0)

        transition.setTargetState(state0)

        self.assertEqual(transition.targetState(), state0)
        self.assertEqual(getrefcount(transition.targetState()), refcount0 + 1)

        state1 = QState()
        state2 = QState()
        states = [state1, state2]
        refcount1 = getrefcount(state1)
        refcount2 = getrefcount(state2)

        transition.setTargetStates(states)

        self.assertEqual(getrefcount(state0), refcount0)
        self.assertEqual(transition.targetStates(), states)
        self.assertEqual(transition.targetState(), state1)
        self.assertEqual(getrefcount(transition.targetStates()[0]), refcount1 + 1)
        self.assertEqual(getrefcount(transition.targetStates()[1]), refcount2 + 1)

        del states
        del transition

        self.assertEqual(getrefcount(state1), refcount1 - 1)
        self.assertEqual(getrefcount(state2), refcount2 - 1)

    def testRefCountOfTargetStatesBeforeSingleTargetState(self):
        transition = QEventTransition()
        state1 = QState()
        state2 = QState()
        states = [state1, state2]
        refcount1 = getrefcount(state1)
        refcount2 = getrefcount(state2)

        transition.setTargetStates(states)

        self.assertEqual(transition.targetStates(), states)
        self.assertEqual(transition.targetState(), state1)
        self.assertEqual(getrefcount(transition.targetStates()[0]), refcount1 + 1)
        self.assertEqual(getrefcount(transition.targetStates()[1]), refcount2 + 1)

        state3 = QState()
        refcount3 = getrefcount(state3)

        transition.setTargetState(state3)

        self.assertEqual(transition.targetState(), state3)
        self.assertEqual(getrefcount(transition.targetState()), refcount3 + 1)

        del states

        self.assertEqual(getrefcount(state1), refcount1 - 1)
        self.assertEqual(getrefcount(state2), refcount2 - 1)

if __name__ == '__main__':
    unittest.main()

