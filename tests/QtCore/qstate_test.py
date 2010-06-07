#!/usr/bin/python
import unittest
from PySide.QtCore import QObject, QState, QFinalState, SIGNAL, QCoreApplication, QTimer, QStateMachine, QSignalTransition, QVariant


class QStateTest(unittest.TestCase):
    def testBasic(self):
        app = QCoreApplication([])

        o = QObject()
        o.setProperty("text", QVariant("INdT"))

        machine = QStateMachine()
        s1 = QState()
        s1.assignProperty(o, "text", QVariant("Rocks"));

        s2 = QFinalState()
        t = s1.addTransition(o, SIGNAL("change()"), s2);
        self.assert_(isinstance(t, QSignalTransition))

        machine.addState(s1)
        machine.addState(s2)
        machine.setInitialState(s1)
        machine.start()

        o.emit(SIGNAL("change()"))

        QTimer.singleShot(100, app.quit)
        app.exec_()

        txt = o.property("text").toString()
        self.assert_(txt, "Rocks")

if __name__ == '__main__':
    unittest.main()
