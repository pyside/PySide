import unittest
from PySide.QtCore import *
from PySide.QtScript import *

class TestQScriptValue (unittest.TestCase):

    def testOperator(self):
        app = QCoreApplication([])

        engine = QScriptEngine()
        value = engine.evaluate('x = {"a": 1, "b":2}')
        self.assertEqual(value['a'], 1)
        self.assertRaises(KeyError, value.__getitem__, 'c')
        value = engine.evaluate('x = ["x", "y", "z"]')
        self.assertEqual(value[2], 'z')
        self.assertRaises(IndexError, value.__getitem__, 23)


if __name__ == '__main__':
    unittest.main()
