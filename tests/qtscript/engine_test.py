import unittest

from PySide.QtCore import QObject
from PySide.QtScript import  QScriptEngine

class QScriptEngineTest(unittest.TestCase):

    def testQScriptEngine(self):
         engine = QScriptEngine()
         obj = engine.evaluate("({ unitName: 'Celsius', toKelvin: function(x) { return x + 273; } })")
         toKelvin = obj.property("toKelvin")
         result = toKelvin.call(obj, [100])
         self.assertEqual(result.toNumber(), 373)
