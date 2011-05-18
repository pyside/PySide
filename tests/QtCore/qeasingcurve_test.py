import unittest

from PySide.QtCore import QEasingCurve

def myFunction(progress):
    if progress == 1.0:
        return 100.0
    else:
        return -100.0

class TestQEasingCurve(unittest.TestCase):
    def testCustomType(self):
        ec = QEasingCurve()
        ec.setCustomType(myFunction)
        self.assertEqual(ec.valueForProgress(1.0), 100.0)
        self.assertEqual(ec.valueForProgress(0.5), -100.0)

    def testObjectCleanup(self):
        for i in range(100):
            ec = QEasingCurve()
            ec.setCustomType(myFunction)
            self.assertEqual(ec.valueForProgress(1.0), 100.0)
            self.assertEqual(ec.valueForProgress(0.5), -100.0)

if __name__ == '__main__':
    unittest.main()
