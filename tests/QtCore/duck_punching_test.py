#!/usr/bin/python

'''Test case for duck punching new implementations of C++ virtual methods into object instances.'''

import unittest
import types
import sys
from PySide.QtCore import QObject
from helper import UsesQCoreApplication

def MethodType(func, instance, instanceType):
    if sys.version_info[0] == 3:
        return types.MethodType(func, instance)
    else:
        return types.MethodType(func, instance, instanceType)

class Duck(QObject):
    def __init__(self):
        QObject.__init__(self)
    def childEvent(self, event):
        QObject.childEvent(self, event)

class TestDuckPunchingOnQObjectInstance(UsesQCoreApplication):
    '''Test case for duck punching new implementations of C++ virtual methods into object instances.'''

    def setUp(self):
        #Acquire resources
        self.duck_childEvent_called = False
        UsesQCoreApplication.setUp(self)

    def tearDown(self):
        #Release resources
        del self.duck_childEvent_called
        UsesQCoreApplication.tearDown(self)


    def testChildEventMonkeyPatch(self):
        #Test if the new childEvent injected on QObject instance is called from C++
        parent = QObject()
        def childEvent(obj, event):
            self.duck_childEvent_called = True
        parent.childEvent = MethodType(childEvent, parent, QObject)
        child = QObject()
        child.setParent(parent)
        self.assert_(self.duck_childEvent_called)
        # This is done to decrease the refcount of the vm object
        # allowing the object wrapper to be deleted before the
        # BindingManager. This is useful when compiling Shiboken
        # for debug, since the BindingManager destructor has an
        # assert that checks if the wrapper mapper is empty.
        parent.childEvent = None

    def testChildEventMonkeyPatchWithInheritance(self):
        #Test if the new childEvent injected on a QObject's extension class instance is called from C++
        parent = Duck()
        def childEvent(obj, event):
            QObject.childEvent(obj, event)
            self.duck_childEvent_called = True
        child = QObject()
        child.setParent(parent)
        parent.childEvent = MethodType(childEvent, parent, QObject)
        child = QObject()
        child.setParent(parent)
        self.assert_(self.duck_childEvent_called)
        # This is done to decrease the refcount of the vm object
        # allowing the object wrapper to be deleted before the
        # BindingManager. This is useful when compiling Shiboken
        # for debug, since the BindingManager destructor has an
        # assert that checks if the wrapper mapper is empty.
        parent.childEvent = None

if __name__ == '__main__':
    unittest.main()

