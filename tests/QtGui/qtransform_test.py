import unittest
from PySide.QtGui import QTransform

class QTransformTest(unittest.TestCase):

    def testMap(self):
        transform = QTransform()
        values = (10.0, 20.0)
        tx, ty = transform.map(*values)
        self.assert_(isinstance(tx, float))
        self.assert_(isinstance(ty, float))
        self.assertEqual((tx, ty), values)

if __name__ == "__main__":
   unittest.main()

