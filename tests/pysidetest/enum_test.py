# -*- coding: utf-8 -*-

import unittest
from testbinding import Enum1, TestObjectWithoutNamespace

class ListConnectionTest(unittest.TestCase):

    def testEnumVisibility(self):
        self.assertEqual(Enum1.Option1, 1)
        self.assertEqual(Enum1.Option2, 2)
        self.assertEqual(TestObjectWithoutNamespace.Enum2.Option3, 3)
        self.assertEqual(TestObjectWithoutNamespace.Enum2.Option4, 4)

if __name__ == '__main__':
    unittest.main()

