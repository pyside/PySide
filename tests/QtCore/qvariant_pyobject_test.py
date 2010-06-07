
'''QVariant handling of PyObjects, including pure-python or derived from Qt'''

import unittest

from PySide.QtCore import QSize, QVariant, QString


class Dummy(object):
    '''Pure python sample class'''
    pass


class MySize(QSize):
    '''Extended class'''
    pass


class QVariantPurePython(unittest.TestCase):
    '''QVariant + pure python classes'''

    def testTypeNamePythonClasses(self):
        '''QVariant of pure python classes'''
        d = Dummy()
        obj = QVariant(d)
        # inherited type name from other binding
        self.assertEqual('PyQt_PyObject', obj.typeName())


class QVariantInheritedPython(unittest.TestCase):
    '''QVariant + classes inherited from C++'''

    # This works only on PyQt4 4.5.x, not on PyQt4 4.4.x or PySide
    def testSubClassConvertion(self):
        '''QVariant(QSize subclass) type is UserType and returns same object'''
        mysize = MySize(0, 0)
        variant = QVariant(mysize)

        self.assertEqual(variant.type(), QVariant.UserType)
        self.assertTrue(variant.toPyObject() is mysize)


class QVariantToPyObject(unittest.TestCase):
    '''QVariant.toPyObject tests'''

    def testQVariantPyList(self):
        '''QVariant(QVariantList).toPyObject() equals original list'''
        obj = QVariant([1, 'two', 3])
        self.assertEqual(obj.toPyObject(), [1, 'two', 3])

    def testPyObject(self):
        '''QVariant(pure PyObject).toPyObject should return the same object'''
        d = Dummy()
        obj = QVariant(d)
        self.assert_(d is obj.toPyObject())

    def testNoneToPyObject(self):
        '''QVariant().toPyObject() should return None'''
        obj = QVariant()
        self.assertEqual(None, obj.toPyObject())

    def testQStringToPyObject(self):
        '''QVariant(python string).toPyObject() return an equal QString'''
        d = 'abc'
        obj = QVariant('abc')
        self.assert_(isinstance(obj.toPyObject(), QString))
        self.assertEqual(d, obj.toPyObject())


if __name__ == '__main__':
    unittest.main()
