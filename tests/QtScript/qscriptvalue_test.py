import unittest
import PySide
from PySide.QtScript import QScriptEngine, QScriptValue

from helper import UsesQApplication

class TestQScriptValue (UsesQApplication):

    def testOperator(self):
        engine = QScriptEngine()
        value = engine.evaluate('x = {"a": 1, "b":2}')
        self.assertEqual(value['a'], 1)
        self.assertRaises(KeyError, value.__getitem__, 'c')
        value = engine.evaluate('x = ["x", "y", "z"]')
        self.assertEqual(value[2], 'z')
        self.assertRaises(IndexError, value.__getitem__, 23)

    def testRepr(self):
        value = QScriptValue("somePerson = { firstName: 'John', lastName: 'Doe' }")
        value2 = eval(repr(value))
        self.assertEqual(value.toString(), value2.toString())

if __name__ == '__main__':
    unittest.main()
