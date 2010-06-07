
import unittest

from PySide.QtCore import SIGNAL
from PySide.QtScript import QScriptEngine
from PySide.QtScriptTools import QScriptEngineDebugger

from helper import UsesQApplication

class DebuggerTest(UsesQApplication):

    def setUp(self):
        UsesQApplication.setUp(self)
        self.engine = QScriptEngine()
        self.debugger = QScriptEngineDebugger()
        self.has_suspended = False
        self.has_resumed = False

    def suspended(self):
        self.has_suspended = True
        self.debugger.action(QScriptEngineDebugger.ContinueAction).trigger()

    def resumed(self):
        self.has_resumed = True

    def testBasic(self):
        '''Interrupt and resume evaluation with QScriptEngineDebugger'''
        self.debugger.attachTo(self.engine)
        self.debugger.setAutoShowStandardWindow(False)
        self.debugger.connect(SIGNAL('evaluationSuspended()'), self.suspended)
        self.debugger.connect(SIGNAL('evaluationResumed()'), self.resumed)

        self.debugger.action(QScriptEngineDebugger.InterruptAction).trigger()
        self.engine.evaluate("3+4")
        self.debugger.action(QScriptEngineDebugger.ContinueAction).trigger()
        self.assert_(self.has_resumed)
        self.assert_(self.has_suspended)


if __name__ == '__main__':
    unittest.main()
