#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test case for the bug #378
http://bugs.openbossa.org/show_bug.cgi?id=378
'''

import unittest
from PySide.QtCore import QObject

class ExtQObject(QObject):
    def __init__(self):
        # "foobar" will become a object attribute that will not be
        # listed on the among the type attributes. Thus for bug
        # condition be correctly triggered the "foobar" attribute
        # must not previously exist in the parent class.
        self.foobar = None
        # The parent __init__ method must be called after the
        # definition of "self.foobar".
        QObject.__init__(self)

class TestBug378(unittest.TestCase):
    '''Test case for the bug #378'''

    def testBug378(self):
        obj = ExtQObject()

if __name__ == '__main__':
    unittest.main()

