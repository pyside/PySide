import unittest

from PySide.QtCore import QByteArray
from helper.docmodifier import DocModifier

class BaseQByteArrayOperatorIAdd(object):
    '''Base class for QByteArray += operator tests.

    Implementing classes should inherit from unittest.TestCase and implement
    setUp, setting self.obj and self.orig_obj to the target QByteArray and original
    one, respectively'''

    __metaclass__ = DocModifier

    def testSingleString(self):
        '''QByteArray += string of size 1'''
        s = '0'
        self.obj += s
        self.assertEqual(self.obj, self.orig_obj + s)
        self.assertEqual(self.obj.size(), self.orig_obj.size() + len(s))

    def testString(self):
        '''QByteArray += string of size > 1'''
        s = 'dummy'
        self.obj += s
        self.assertEqual(self.obj, self.orig_obj + s)
        self.assertEqual(self.obj.size(), self.orig_obj.size() + len(s))

    def testQByteArray(self):
        '''QByteArray += QByteArray'''
        s = QByteArray('array')
        self.obj += s
        self.assertEqual(self.obj, self.orig_obj + s)

    def testChar(self):
        '''QByteArray += char (number < 256)'''
        s = ord('a')
        self.obj += s
        self.assertEqual(self.obj, self.orig_obj + s)
        self.assertEqual(self.obj.size(), self.orig_obj.size() + 1)

class NullQByteArrayOperatorIAdd(unittest.TestCase, BaseQByteArrayOperatorIAdd):
    '''Test case for operator QByteArray += on null QByteArrays'''

    doc_prefix = 'Null object'
    doc_filter = lambda x: x.startswith('test')

    def setUp(self):
        self.obj = QByteArray()
        self.orig_obj = QByteArray()


class ValidQByteArrayOperatorIAdd(unittest.TestCase, BaseQByteArrayOperatorIAdd):
    '''Test case for operator QByteArray += on valid QByteArrays'''

    doc_prefix = 'Valid object'
    doc_filter = lambda x: x.startswith('test')

    def setUp(self):
        self.obj = QByteArray('some byte array')
        self.orig_obj = QByteArray('some byte array')

if __name__ == '__main__':
    unittest.main()
