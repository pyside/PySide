import unittest
from PySide.QtCore import QSysInfo

class TestQSysInfo(unittest.TestCase):
    def testEnumEndian(self):
        self.assertEqual(QSysInfo.BigEndian, 0)
        self.assertEqual(QSysInfo.LittleEndian, 1)
        self.assert_(QSysInfo.ByteOrder > -1)

    def testEnumSizes(self):
        self.assert_(QSysInfo.WordSize > 0)

if __name__ == '__main__':
    unittest.main()
