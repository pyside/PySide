
'''Test cases for QObject property and setProperty'''

import unittest

from PySide.QtCore import *

class Dummy(object):
    '''Pure python sample class'''
    pass

class MySize(QSize):
    '''Extended class'''
    pass

class ExQObject(QObject):
    def __init__(self, *args, **kargs):
        QObject.__init__(self, *args, **kargs)

    def setProperty(self, value):
        self._value = value

    def getProperty(self):
        return self._value

    registeredproperty = Property(int, getProperty, setProperty)

class MyObject(QObject):
    '''Test Property'''

    def readPP(self):
        return 42

    def trySetPP(self):
        self.pp = 0

    pp = Property(int, readPP, constant=True)

class MyObjectWithNotifyProperty(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self.p = 0

    def readP(self):
        return self.p

    def writeP(self, v):
        self.p = v
        self.notifyP.emit()

    notifyP = Signal()
    myProperty = Property(int, readP, fset=writeP, notify=notifyP)

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

    def testValueType(self):
        rect = QRect(1, 2, 3, 4)
        obj = QObject()
        obj.setProperty('rect', rect)
        '''Value types when converted to QVariant is copyed'''
        self.assertFalse(obj.property('rect') is rect)
        self.assertEqual(obj.property('rect'), rect)

class PropertyWithConstructorCase(unittest.TestCase):
    '''Test case for QObject properties set using named arguments in the constructor.'''

    def testObjectNameProperty(self):
        #QObject(property=value) for existing C++ property
        obj = QObject(objectName='dummy')
        self.assertEqual(obj.objectName(), 'dummy')

    def testDynamicPropertyRaisesException(self):
        self.assertRaises(AttributeError, QObject, dummy=42)

    def testPythonDeclaredProperty(self):
        obj = ExQObject(registeredproperty=123)
        self.assertEqual(obj.registeredproperty, 123)

    def testPythonDeclaredPropertyNoSetted(self):
        try:
            obj = ExQObject()
            a = obj.registeredproperty
        except AttributeError:
            pass

    def testConstructorPropertyInQObjectDerived(self):
        #QTimer(property=value) for existing C++ property
        obj = QTimer(objectName='dummy')
        self.assertEqual(obj.objectName(), 'dummy')

    def testReadOnlyPythonProperty(self):
        o = MyObject()
        self.assertEqual(o.pp, 42)
        self.assertRaises(AttributeError, o.trySetPP)

class PropertyWithNotify(unittest.TestCase):
    def called(self):
        self.called_ = True

    def testMetaData(self):
        obj = MyObjectWithNotifyProperty()
        mo = obj.metaObject()
        self.assertEqual(mo.propertyCount(), 2)
        p = mo.property(1)
        self.assertEqual(p.name(), "myProperty")
        self.assert_(p.hasNotifySignal())

    def testNotify(self):
        self.called_ = False
        obj = MyObjectWithNotifyProperty()
        obj.notifyP.connect(self.called)
        obj.myProperty = 10
        self.assert_(self.called_)

class MetaPropertyTest(unittest.TestCase):
    def testConstant(self):
        obj = MyObject()
        mo = obj.metaObject()
        self.assertEqual(mo.propertyCount(), 2)
        p = mo.property(1)
        self.assertTrue(p.isConstant())

        obj = MyObjectWithNotifyProperty()
        mo = obj.metaObject()
        self.assertEqual(mo.propertyCount(), 2)
        p = mo.property(1)
        self.assertFalse(p.isConstant())

if __name__ == '__main__':
    unittest.main()

