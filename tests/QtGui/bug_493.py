from PySide.QtCore import Qt, QEvent
from PySide.QtGui import QApplication, QKeyEvent, QKeySequence
import unittest


class TestBug569(unittest.TestCase):

    def testIt(self):
        # We need a qapp otherwise Qt will crash when trying to detect the
        # current platform
        app = QApplication([])
        ev1 = QKeyEvent(QEvent.KeyRelease, Qt.Key_Delete, Qt.NoModifier)
        ev2 = QKeyEvent(QEvent.KeyRelease, Qt.Key_Copy, Qt.NoModifier)
        ks = QKeySequence.Delete

        self.assertEqual(ev1, ks)
        self.assertEqual(ks, ev1)
        self.assertNotEqual(ev2, ks)
        self.assertNotEqual(ks, ev2)

if __name__ == '__main__':
    unittest.main()
