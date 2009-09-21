#!/usr/bin/python
'''Unit tests for QDataStream'''

import unittest

from PySide.QtCore import QDataStream, QBuffer

class QDataStreamTest(unittest.TestCase):
    '''Test case for QByteArray.split'''

    def testWriteFunction(self):
        b = QBuffer()
        b.open(QBuffer.ReadWrite)
        ds = QDataStream(b)
        ds.writeUInt8(chr(True))
        self.assertEqual(b.buffer().at(0), chr(True))


if __name__ == '__main__':
    unittest.main()
