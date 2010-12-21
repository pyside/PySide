import unittest

import sys
from PySide.QtCore import QT_TR_NOOP, QT_TR_NOOP_UTF8
from PySide.QtCore import QT_TRANSLATE_NOOP, QT_TRANSLATE_NOOP3, QT_TRANSLATE_NOOP_UTF8

class QtTrNoopTest(unittest.TestCase):

    def setUp(self):
        self.txt = 'Cthulhu fhtag!'

    def tearDown(self):
        del self.txt

    def testQtTrNoop(self):
        refcnt = sys.getrefcount(self.txt)
        result = QT_TR_NOOP(self.txt)
        self.assertEqual(result, self.txt)
        self.assertEqual(sys.getrefcount(result), refcnt + 1)

    def testQtTrNoopUtf8(self):
        refcnt = sys.getrefcount(self.txt)
        result = QT_TR_NOOP_UTF8(self.txt)
        self.assertEqual(result, self.txt)
        self.assertEqual(sys.getrefcount(result), refcnt + 1)

    def testQtTranslateNoop(self):
        refcnt = sys.getrefcount(self.txt)
        result = QT_TRANSLATE_NOOP(None, self.txt)
        self.assertEqual(result, self.txt)
        self.assertEqual(sys.getrefcount(result), refcnt + 1)

    def testQtTranslateNoopUtf8(self):
        refcnt = sys.getrefcount(self.txt)
        result = QT_TRANSLATE_NOOP_UTF8(self.txt)
        self.assertEqual(result, self.txt)
        self.assertEqual(sys.getrefcount(result), refcnt + 1)

    def testQtTranslateNoop3(self):
        refcnt = sys.getrefcount(self.txt)
        result = QT_TRANSLATE_NOOP3(None, self.txt, None)
        self.assertEqual(result, self.txt)
        self.assertEqual(sys.getrefcount(result), refcnt + 1)


if __name__ == '__main__':
    unittest.main()

