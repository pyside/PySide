import unittest

from PySide.QtGui import QMatrix4x4

class TestQMatrix(unittest.TestCase):
    def testOperator(self):
        m = QMatrix4x4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)
        v = 1
        for x in range(4):
            for y in range(4):
                self.assertEqual(m[x,y], v)
                v += 1

if __name__ == '__main__':
    unittest.main()
