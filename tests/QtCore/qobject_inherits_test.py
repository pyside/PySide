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


if __name__ == '__main__':
    unittest.main()
