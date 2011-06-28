'''Test cases for QObject methods'''

import unittest

from PySide.QtCore import QObject

class InheritsCase(unittest.TestCase):
    '''Test case for QObject.inherits'''

    def testCppInheritance(self):
        #QObject.inherits() for c++ classes
        #An class inherits itself
        self.assert_(QObject().inherits('QObject'))

    def testPythonInheritance(self):
        #QObject.inherits() for python classes

        class Dummy(QObject):
            #Dummy class
            pass

        self.assert_(Dummy().inherits('QObject'))
        self.assert_(Dummy().inherits('Dummy'))
        self.assert_(not Dummy().inherits('FooBar'))

    def testPythonMultiInheritance(self):
        #QObject.inherits() for multiple inheritance
        # QObject.inherits(classname) should fail if classname isn't a
        # QObject subclass

        class Parent(object):
            #Dummy parent
            pass
        class Dummy(QObject, Parent):
            #Dummy class
            pass

        self.assert_(Dummy().inherits('QObject'))
        self.assert_(not Dummy().inherits('Parent'))

    def testSetAttributeBeforeCallingInitOnQObjectDerived(self):
        '''Test for bug #428.'''
        class DerivedObject(QObject):
            def __init__(self):
                self.member = 'member'
                QObject.__init__(self)
        obj0 = DerivedObject()
        # The second instantiation of DerivedObject will generate an exception
        # that will not come to surface immediately.
        obj1 = DerivedObject()
        # The mere calling of the object method causes
        # the exception to "reach the surface".
        obj1.objectName()

    def testMultipleInheritance(self):
        def declareClass():
            class Foo(object, QObject):
                pass

        self.assertRaises(TypeError, declareClass)

if __name__ == '__main__':
    unittest.main()
