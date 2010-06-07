#!/usr/bin/python
'''Test cases for overloads involving static and non-static versions of a method.'''

import os
import unittest

from PySide.QtCore import QFile

class StaticNonStaticMethodsTest(unittest.TestCase):
    '''Test cases for overloads involving static and non-static versions of a method.'''

    def setUp(self):
        filename = 'somefile%d.txt' % os.getpid()
        self.existing_filename = os.path.join(os.path.curdir, filename)
        self.delete_file = False
        if not os.path.exists(self.existing_filename):
            f = open(self.existing_filename, 'w')
            for line in range(10):
                f.write('sbrubbles\n')
            f.close()
            self.delete_file = True

        self.non_existing_filename = os.path.join(os.path.curdir, 'inexistingfile.txt')
        i = 0
        while os.path.exists(self.non_existing_filename):
            i += 1
            filename = 'inexistingfile-%d.txt' % i
            self.non_existing_filename = os.path.join(os.path.curdir, filename)

    def tearDown(self):
        if self.delete_file:
            os.remove(self.existing_filename)

    def testCallingStaticMethodWithClass(self):
        '''Call static method using class.'''
        self.assert_(QFile.exists(self.existing_filename))
        self.assertFalse(QFile.exists(self.non_existing_filename))

    def testCallingStaticMethodWithInstance(self):
        '''Call static method using instance of class.'''
        f = QFile(self.non_existing_filename)
        self.assert_(f.exists(self.existing_filename))
        self.assertFalse(f.exists(self.non_existing_filename))

    def testCallingInstanceMethod(self):
        '''Call instance method.'''
        f1 = QFile(self.non_existing_filename)
        self.assertFalse(f1.exists())
        f2 = QFile(self.existing_filename)
        self.assert_(f2.exists())


if __name__ == '__main__':
    unittest.main()

