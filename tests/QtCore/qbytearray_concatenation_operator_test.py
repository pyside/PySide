#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QByteArray concatenation with '+' operator'''

import unittest

from PySide.QtCore import QByteArray

class QByteArrayConcatenationOperatorTest(unittest.TestCase):
    '''Test cases for QByteArray concatenation with '+' operator'''

    def testConcatQByteArrayAndPythonString(self):
        #Test concatenation of a QByteArray with a Python string, in this order
        qba = QByteArray('foo')
        result = qba + '\x00bar'
        self.assertEqual(type(result), QByteArray)
        self.assertEqual(result, 'foo\x00bar')

    def testConcatPythonStringAndQByteArray(self):
        #Test concatenation of a Python string with a QByteArray, in this order
        concat_python_string_add_qbytearray_worked = True
        qba = QByteArray('foo')
        result = 'bar\x00' + qba
        self.assertEqual(type(result), QByteArray)
        self.assertEqual(result, 'bar\x00foo')

    # NOTICE: Does not makes sense concat a unicode string with a QByteArray, because the
    # user does not know nothing about the internal representation of the unicode string.
    #def testConcatPythonUnicodeAndQByteArray(self):
        ##Test concatenation of a Python unicode object with a QByteArray, in this order
        #concat_python_unicode_add_qbytearray_worked = True
        #qba = QByteArray('foo')
        #result = None
        #try:
            #result = u'ümlaut' + qba
        #except:
            #concat_python_unicode_add_qbytearray_worked = False
        #self.assertTrue(concat_python_unicode_add_qbytearray_worked)
        #self.assertEqual(result.__class__.__name__, 'unicode')

if __name__ == '__main__':
    unittest.main()

