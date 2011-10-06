#!/usr/bin/python
'''Unit tests for QDataStream'''

import unittest
import py3kcompat as py3k

from PySide.QtCore import QBitArray, QByteArray, QIODevice, QDataStream, QDate, QTime, QDateTime

def create_bitarray(string):
    array = QBitArray(len(string))
    for i, char in enumerate(string):
        array.setBit(i, char != '0')
    return array

class QDataStreamWrite(unittest.TestCase):
    '''Test case for QDatastream write* functions'''

    def setUp(self):
        self.ba = QByteArray()
        self.read = QDataStream(self.ba, QIODevice.ReadOnly)
        self.write = QDataStream(self.ba, QIODevice.WriteOnly)

    def testWriteUInt8(self):
        '''QDataStream.writeUInt8 (accepting str of size 1)'''
        x = 0xFF
        self.write.writeUInt8(x)
        y = self.read.readUInt8()
        self.assertEqual(x, y)

        self.assertRaises(TypeError, self.write.writeUInt8, 'aaaaa')

    def testWriteInt8(self):
        '''QDataStream.writeInt8 (accepting str of size 1)'''
        x = 65
        self.write.writeInt8(chr(x))
        y = self.read.readInt8()
        self.assertEqual(x, y)

        self.assertRaises(TypeError, self.write.writeInt8, 'aaaaa')

    def testWriteUInt8Int(self):
        '''QDataStream.writeUInt8 (accepting integer)'''
        x = 0xFF
        self.write.writeUInt8(x)
        y = self.read.readUInt8()
        self.assertEqual(x, y)

    def testWriteInt8Int(self):
        '''QDataStream.writeInt8 (accepting integer)'''
        x = 65
        self.write.writeInt8(x)
        y = self.read.readInt8()
        self.assertEqual(x, y)

    def testWriteUInt16(self):
        '''QDataStream.writeUInt16'''
        x = 0x4423
        self.write.writeUInt16(x)
        y = int(self.read.readUInt16())
        self.assertEqual(x, y)

    def testWriteUInt32(self):
        '''QDataStream.writeUInt32'''
        x = 0xdeadbeef
        self.write.writeUInt32(x)
        y = int(self.read.readUInt32())
        self.assertEqual(x, y)

class QDataStreamShift(unittest.TestCase):
    '''Test case for << and >> operators'''

    def setUp(self):
        self.ba = QByteArray()
        self.stream = QDataStream(self.ba, QIODevice.WriteOnly)
        self.read_stream = QDataStream(self.ba, QIODevice.ReadOnly)

    def testQCharValid(self):
        '''QDataStream <<>> QChar - valid'''
        self.stream.writeQChar(42)

        res = self.read_stream.readQChar()
        self.assertEqual(res, py3k.unichr(42))

    def testQCharNull(self):
        '''QDataStream <<>> QChar - null'''
        self.stream.writeQChar(None)

        res = self.read_stream.readQChar()
        self.assertEqual(res, py3k.unicode_('\x00'))

    def testQByteArrayValid(self):
        '''QDataStream <<>> QByteArray - valid'''
        self.stream << QByteArray("hello")

        res = QByteArray()

        self.read_stream >> res
        self.assertEqual(res, QByteArray("hello"))

    def testQByteArrayEmpty(self):
        '''QDataStream <<>> QByteArray - empty'''
        self.stream << QByteArray("")

        res = QByteArray()

        self.read_stream >> res
        self.assertEqual(res, QByteArray(""))
        self.assertTrue(res.isEmpty())
        self.assertFalse(res.isNull())

    def testQByteArrayNull(self):
        '''QDataStream <<>> QByteArray - null'''
        self.stream << QByteArray()

        res = QByteArray()

        self.read_stream >> res
        self.assertEqual(res, QByteArray())
        self.assertTrue(res.isEmpty())
        self.assertTrue(res.isNull())

    def testQStringValid(self):
        '''QDataStream <<>> QString - valid'''
        self.stream.writeQString('Ka-boom')

        res = self.read_stream.readQString()
        self.assertEqual(res, py3k.unicode_('Ka-boom'))

    def testQStringEmpty(self):
        '''QDataStream <<>> QString - empty'''
        self.stream.writeQString('')

        res = self.read_stream.readQString()
        self.assertEqual(res, py3k.unicode_(''))

    def testQStringNull(self):
        '''QDataStream <<>> QString - null'''
        self.stream.writeQString(None)

        res = self.read_stream.readQString()
        self.assertEqual(res, py3k.unicode_(''))

    def testQBitArrayNull(self):
        '''QDataStream <<>> QBitArray - null'''
        self.stream << QBitArray()

        res = QBitArray()

        self.read_stream >> res
        self.assertEqual(res, QBitArray())

    def testQBitArrayValid(self):
        '''QDataStream <<>> QBitArray - valid'''
        self.stream << create_bitarray('01010101')

        res = QBitArray()

        self.read_stream >> res
        self.assertEqual(res, create_bitarray('01010101'))

    def testQDateNull(self):
        '''QDataStream <<>> QDate - null'''
        self.stream << QDate()

        res = QDate()

        self.read_stream >> res
        self.assertEqual(res, QDate())
        self.assertFalse(res.isValid())
        self.assertTrue(res.isNull())

    def testQDateValid(self):
        '''QDataStream <<>> QDate - valid'''
        self.stream << QDate(2012, 12, 21)

        res = QDate()

        self.read_stream >> res
        self.assertEqual(res, QDate(2012, 12, 21))
        self.assertTrue(res.isValid())
        self.assertFalse(res.isNull())


    def testQTimeNull(self):
        '''QDataStream <<>> QTime - null'''
        self.stream << QTime()

        res = QTime()

        self.read_stream >> res
        self.assertEqual(res, QTime())
        self.assertFalse(res.isValid())
        self.assertTrue(res.isNull())

    def testQTimeValid(self):
        '''QDataStream <<>> QTime - valid'''
        self.stream << QTime(12, 12, 21)

        res = QTime()

        self.read_stream >> res
        self.assertEqual(res, QTime(12, 12, 21))
        self.assertTrue(res.isValid())
        self.assertFalse(res.isNull())

    def testQDateTimeNull(self):
        '''QDataStream <<>> QDateTime - null'''

        self.stream << QDateTime()

        res = QDateTime()

        self.read_stream >> res
        self.assertEqual(res, QDateTime())
        self.assertFalse(res.isValid())
        self.assertTrue(res.isNull())

    def testQDateTimeValid(self):
        '''QDataStream <<>> QDateTime - valid'''
        time = QTime(23, 23, 23)
        date = QDate(2009, 1, 1)

        self.stream << QDateTime(date, time)

        res = QDateTime()

        self.read_stream >> res
        self.assertEqual(res, QDateTime(date, time))
        self.assertTrue(res.isValid())
        self.assertFalse(res.isNull())


class QDataStreamShiftBitArray(unittest.TestCase):

    def _check_bitarray(self, data_set):
        '''Check the >> operator for the given data set'''

        for data, expectedStatus, expectedString in data_set:
            stream = QDataStream(data, QIODevice.ReadOnly)
            string = QBitArray()
            stream >> string

            self.assertEqual(stream.status(), expectedStatus)
            self.assertEqual(string.size(), expectedString.size())
            self.assertEqual(string, expectedString)

    def testOk(self):
        '''QDataStream with valid QBitArray'''
        data = []

        data.append((QByteArray('\x00\x00\x00\x00'), QDataStream.Ok,
                     QBitArray()))
        data.append((QByteArray('\x00\x00\x00\x01\x00'), QDataStream.Ok,
                     create_bitarray('0')))
        data.append((QByteArray('\x00\x00\x00\x01\x01'), QDataStream.Ok,
                     create_bitarray('1')))
        data.append((QByteArray('\x00\x00\x00\x02\x03'), QDataStream.Ok,
                     create_bitarray('11')))
        data.append((QByteArray('\x00\x00\x00\x03\x07'), QDataStream.Ok,
                     create_bitarray('111')))
        data.append((QByteArray('\x00\x00\x00\x04\x0f'), QDataStream.Ok,
                     create_bitarray('1111')))
        data.append((QByteArray('\x00\x00\x00\x05\x1f'), QDataStream.Ok,
                     create_bitarray('11111')))
        data.append((QByteArray('\x00\x00\x00\x06\x3f'), QDataStream.Ok,
                     create_bitarray('111111')))
        data.append((QByteArray('\x00\x00\x00\x07\x7f'), QDataStream.Ok,
                     create_bitarray('1111111')))
        data.append((QByteArray('\x00\x00\x00\x07\x7e'), QDataStream.Ok,
                     create_bitarray('0111111')))
        data.append((QByteArray('\x00\x00\x00\x07\x00'), QDataStream.Ok,
                     create_bitarray('0000000')))
        data.append((QByteArray('\x00\x00\x00\x07\x39'), QDataStream.Ok,
                     create_bitarray('1001110')))

        self._check_bitarray(data)

    def testPastEnd(self):
        '''QDataStream >> QBitArray reading past the end of the data'''
        data = []

        data.append((QByteArray(), QDataStream.ReadPastEnd,
                     QBitArray()))
        data.append((QByteArray('\x00'), QDataStream.ReadPastEnd,
                     QBitArray()))
        data.append((QByteArray('\x00\x00'), QDataStream.ReadPastEnd,
                     QBitArray()))
        data.append((QByteArray('\x00\x00\x00'), QDataStream.ReadPastEnd,
                     QBitArray()))
        data.append((QByteArray('\x00\x00\x00\x01'), QDataStream.ReadPastEnd,
                     QBitArray()))
        data.append((QByteArray('\x00\x00\x00\x02'), QDataStream.ReadPastEnd,
                     QBitArray()))
        data.append((QByteArray('\x00\x00\x00\x03'), QDataStream.ReadPastEnd,
                     QBitArray()))
        data.append((QByteArray('\x00\x00\x00\x04'), QDataStream.ReadPastEnd,
                     QBitArray()))

        self._check_bitarray(data)

    def testCorruptData(self):
        '''QDataStream reading corrupt data'''
        data = []

        data.append((QByteArray('\x00\x00\x00\x01\x02'),
                     QDataStream.ReadCorruptData,
                     QBitArray()))

        self._check_bitarray(data)

class QDataStreamRawData(unittest.TestCase):
    def testRawData(self):
        data = QDataStream()
        self.assertEqual(data.readRawData(4), None)

        ba = QByteArray()
        data = QDataStream(ba, QIODevice.WriteOnly)
        data.writeRawData('AB\x00C')
        self.assertEqual(ba.data(), py3k.b('AB\x00C'))

        data = QDataStream(ba)
        self.assertEqual(data.readRawData(4), py3k.b('AB\x00C'))

if __name__ == '__main__':
    unittest.main()

