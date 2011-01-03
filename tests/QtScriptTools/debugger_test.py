
import unittest

from PySide.QtCore import SIGNAL, QTimer
from PySide.QtScript import QScriptEngine
from PySide.QtScriptTools import QScriptEngineDebugger

from helper import UsesQApplication

class DebuggerTest(UsesQApplication):

    def setUp(self):
        UsesQApplication.setUp(self)
        self.engine = QScriptEngine()
        self.debugger = QScriptEngineDebugger()
        self.has_suspended = 0
        self.has_resumed = 0
        self.count = 3

    def suspended(self):
        self.has_suspended += 1
        # Will emit evaluationResumed until there are more instructions to be run
        QTimer.singleShot(100, self.debugger.action(QScriptEngineDebugger.StepIntoAction).trigger)

    def resumed(self):
        # Will be called when debugger.state() change from Suspended to Running
        # except for the first time.
        self.has_resumed += 1

    def testBasic(self):
        '''Interrupt and resume evaluation with QScriptEngineDebugger'''

        self.debugger.attachTo(self.engine)
        self.debugger.setAutoShowStandardWindow(False)
        self.debugger.connect(SIGNAL('evaluationSuspended()'), self.suspended)
        self.debugger.connect(SIGNAL('evaluationResumed()'), self.resumed)

        self.debugger.action(QScriptEngineDebugger.InterruptAction).trigger()
        self.engine.evaluate("3+4\n2+1\n5+1")
        self.assert_(self.has_resumed >= 1)
        self.assert_(self.has_suspended >= 1)

if __name__ == '__main__':
    unittest.main()
