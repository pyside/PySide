import unittest

from PySide.QtCore import *
from PySide.QtScript import *

class QScriptValueTest(unittest.TestCase):
    def testQScriptValue(self): 
        app = QCoreApplication([])
        engine = QScriptEngine()
        repr(engine.evaluate('1 + 1'))

if __name__ == '__main__':
    unittest.main()
