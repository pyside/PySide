from PySide.QtCore import *

import unittest

get_counter = 0
set_counter = 0

class Descriptor(object):
    def __get__(self, obj, owner):
        global get_counter

        if not obj:
            return self

        get_counter += 1
        return obj.var

    def __set__(self, obj, value):
        global set_counter

        set_counter += 1
        obj.var = value

class FooBar(QObject):
    test = Descriptor()
    var = 0

class SetAndGetTestCases(unittest.TestCase):
    def setUp(self):
        global get_counter
        global set_counter

        get_counter = 0
        set_counter = 0

    def testSetMethod(self):
        global get_counter
        global set_counter

        f = FooBar()

        f.test = 1
        self.assertEqual(get_counter, 0)
        self.assertEqual(set_counter, 1)

        get_counter = 0
        set_counter = 0

    def testGetMethod(self):
        global get_counter
        global set_counter

        f = FooBar()
        f.test = 1
        set_counter = 0

        ret = f.test
        self.assertEqual(get_counter, 1)
        self.assertEqual(set_counter, 0)

        get_counter = 0
        set_counter = 0

if __name__ == "__main__":
    unittest.main()
