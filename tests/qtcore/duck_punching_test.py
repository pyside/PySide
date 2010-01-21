#!/usr/bin/python

'''Test case for duck punching new implementations of C++ virtual methods into object instances.'''

import unittest
import types
from PySide.QtCore import QObject, QEvent
from helper import UsesQCoreApplication

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
            QObject.childEvent(obj, event)
        parent.event = types.MethodType(childEvent, parent, QObject)
        child = QObject()
        child.setParent(parent)
        self.assert_(self.duck_childEvent_called)

    def testChildEventMonkeyPatchWithInheritance(self):
        #Test if the new childEvent injected on a QObject's extension class instance is called from C++
        parent = Duck()
        def childEvent(obj, event):
            QObject.childEvent(obj, event)
            self.duck_childEvent_called = True
        child = QObject()
        child.setParent(parent)
        parent.event = types.MethodType(childEvent, parent, QObject)
        child = QObject()
        child.setParent(parent)
        self.assert_(self.duck_childEvent_called)

if __name__ == '__main__':
    unittest.main()

