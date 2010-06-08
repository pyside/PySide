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
        result = qba + 'bar'
        self.assert_(isinstance(result, QByteArray))
        self.assertEqual(result, 'foobar')
        # NOTICE: the standard behavior of PyQt is to return a QString object
        # for this case. As this is a minor issue the assertion will be left commented.
        #self.assertEqual(result.__class__.__name__, 'QString')

    def testConcatPythonStringAndQByteArray(self):
        #Test concatenation of a Python string with a QByteArray, in this order
        concat_python_string_add_qbytearray_worked = True
        qba = QByteArray('foo')
        result = 'bar' + qba
        self.assert_(isinstance(result, QByteArray))
        self.assertEqual(result, 'barfoo')

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

