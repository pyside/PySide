
'''Test cases for QObject property and setProperty'''

import unittest

from PySide.QtCore import *

class Dummy(object):
    '''Pure python sample class'''
    pass

class MySize(QSize):
    '''Extended class'''
    pass

class ExtQObject(QObject):
    registeredproperty = QProperty(int)


class PropertyCase(unittest.TestCase):
    '''Test case for QObject properties'''

    def testObjectNameProperty(self):
        #QObject.setProperty() for existing C++ property
        obj = QObject()
        self.assert_(obj.setProperty('objectName', 'dummy'))
        self.assertEqual(obj.objectName(), 'dummy')

        self.assert_(obj.setProperty('objectName', 'foobar'))
        self.assertEqual(obj.objectName(), 'foobar')

    def testDynamicProperty(self):
        #QObject.setProperty() for dynamic properties
        obj = QObject()

        # Should return false when creating a new dynamic property
        self.assert_(not obj.setProperty('dummy', 'mydata'))
        prop = obj.property('dummy')
        self.assert_(isinstance(prop, unicode))
        self.assertEqual(obj.property('dummy'), 'mydata')

        self.assert_(not obj.setProperty('dummy', 'zigzag'))
        prop = obj.property('dummy')
        self.assert_(isinstance(prop, unicode))
        self.assertEqual(obj.property('dummy'), 'zigzag')

        self.assert_(not obj.setProperty('dummy', 42))
        prop = obj.property('dummy')
        self.assert_(isinstance(prop, int))
        # QVariant.toInt has a bool* arg in C++, so returns a tuple
        self.assertEqual(obj.property('dummy'), 42)

    def testStringProperty(self):
        obj = QObject()
        self.assert_(not obj.setProperty('dummy', 'data'))
        prop = obj.property('dummy')

        self.assert_(isinstance(prop, unicode))
        self.assertEqual(obj.property('dummy'), 'data')

    def testImplicitQVariantProperty(self):
        obj = QObject()
        self.assert_(not obj.setProperty('dummy', 'data'))
        prop = obj.property('dummy')

        self.assert_(isinstance(prop, unicode))
        self.assertEqual(obj.property('dummy'), 'data')

    def testInvalidProperty(self):
        #QObject.property() for invalid properties
        obj = QObject()

        prop = obj.property('dummy')
        self.assertEqual(prop, None)

    def testTypeNamePythonClasses(self):
        '''QVariant of pure python classes'''
        d = Dummy()
        obj = QObject()
        obj.setProperty('foo', d)
        # inherited type name from other binding
        self.assertEqual(obj.property('foo'), d)

    def testQVariantPyList(self):
        '''QVariant(QVariantList).toPyObject() equals original list'''
        obj = QObject()
        obj.setProperty('foo', [1, 'two', 3])
        self.assertEqual(obj.property('foo'), [1, 'two', 3])

    def testSubClassConvertion(self):
        '''QVariant(QSize subclass) type is UserType and returns same object'''
        mysize = MySize(0, 0)
        obj = QObject()
        obj.setProperty('foo', mysize)

        self.assertTrue(obj.property('foo') is mysize)


class PropertyWithConstructorCase(unittest.TestCase):
    '''Test case for QObject properties set using named arguments in the constructor.'''

    def testObjectNameProperty(self):
        #QObject(property=value) for existing C++ property
        obj = QObject(objectName='dummy')
        self.assertEqual(obj.objectName(), 'dummy')

    def testDynamicPropertyRaisesException(self):
        self.assertRaises(AttributeError, QObject, dummy=42)

    def testPythonDeclaredProperty(self):
        obj = ExtQObject(registeredproperty=123)

    def testConstructorPropertyInQObjectDerived(self):
        #QTimer(property=value) for existing C++ property
        obj = QTimer(objectName='dummy')
        self.assertEqual(obj.objectName(), 'dummy')


if __name__ == '__main__':
    unittest.main()

