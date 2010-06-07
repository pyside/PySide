import unittest

from PySide.QtGui import QApplication, QLCDNumber

class QLCDNumberOverflow(unittest.TestCase):
    '''Test case for unhandled overflow on QLCDNumber() numDigits argument (see bug #215).'''

    def setUp(self):
        self.app = QApplication([])

    def testnumDigitsOverflow(self):
        # NOTE: PyQt4 raises TypeError, but boost.python raises OverflowError
        self.assertRaises(OverflowError, QLCDNumber, 840835495615213080)

if __name__ == '__main__':
    unittest.main()
