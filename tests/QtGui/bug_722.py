import unittest

from helper import UsesQApplication

from PySide.QtGui import QDoubleSpinBox, QGraphicsBlurEffect

class TestSignalConnection(UsesQApplication):
    def testFloatSignal(self):
        foo1 = QDoubleSpinBox()
        foo2 = QDoubleSpinBox()
        foo1.valueChanged[float].connect(foo2.setValue)
        foo2.valueChanged[float].connect(foo1.setValue)
        foo1.setValue(0.42)
        self.assertEqual(foo1.value(), foo2.value())

    def testQRealSignal(self):
        foo1 = QDoubleSpinBox()
        effect = QGraphicsBlurEffect()
        effect.blurRadiusChanged['qreal'].connect(foo1.setValue) # check if qreal is a valid type
        effect.setBlurRadius(0.42)
        self.assertAlmostEqual(foo1.value(), effect.blurRadius())

if __name__ == '__main__':
    unittest.main()
