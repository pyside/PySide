import unittest

from PySide.QtGui import QMatrix4x4

class QMatrixTest(unittest.TestCase):
    def testMatrix4x4(self):
        self.assertRaises(TypeError, QMatrix4x4, [0.0, 1.0, 2.0, 3.0])
        self.assertRaises(TypeError, QMatrix4x4, [0.0, 1.0, 2.0, 'I',
                                                  4.0, 5.0, 6.0, 7.0,
                                                  8.0, 9.0, 'N', 11.0,
                                                  12.0, 'd', 14.0, 'T'])

        my_data = [0.0, 1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0, 7.0,
                   8.0, 9.0, 10.0, 11.0,
                   12.0, 13.0, 14.0, 15.0]
        my_datac = [0.0, 4.0, 8.0, 12.0,
                    1.0, 5.0, 9.0, 13.0,
                    2.0, 6.0, 10.0, 14.0,
                    3.0, 7.0, 11.0, 15.0]

        m = QMatrix4x4(my_data)
        d = m.data()
        self.assert_(my_datac, d)

        d = m.copyDataTo()
        self.assert_(my_data == list(d))

if __name__ == '__main__':
    unittest.main()

