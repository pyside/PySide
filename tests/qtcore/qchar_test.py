
'''Test cases for QChar'''

import unittest

from PySide.QtCore import QString, QChar, QTextStream, QLatin1Char


class EqualTest(unittest.TestCase):
    '''Tests for '__equal__'''

    def testEqualQChar(self):
        '''QChar == QChar'''
        self.assertEqual(QChar('a'), QChar('a'))

    def testEqualPyString(self):
        '''QChar == Python string'''
        self.assertEqual(QChar('a'), 'a')


class ImplicitConvQLatin1Char(unittest.TestCase):
    '''Tests for implicit conversion from QLatin1Char to QChar'''

    def testQLatin1CharToChar(self):
        '''QLatin1Char implicitly convertible to QChar'''
        stream = QTextStream()
        stream.setPadChar(QLatin1Char('-'))
        self.assertEqual(QChar('-'), stream.padChar())


class QCharCtorBigNumber(unittest.TestCase):
    '''QChar constructors receiving ints'''

    def testInt(self):
        '''QChar(int)'''
        codepoint = 512
        qchar = QChar(codepoint)
        reference = unichr(codepoint)
        self.assertEqual(qchar.unicode(), codepoint)


if __name__ == '__main__':
    unittest.main()

