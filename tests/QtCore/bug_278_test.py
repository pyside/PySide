#!/usr/bin/python

import unittest

from PySide import QtCore

def setValue(o):
    values = ['Name']
    o.setProperty('test1', values)

class QQtVersionTest(unittest.TestCase):
    '''Tests for QVariant conversion of QStringList'''

    def testGet(self):
        o = QtCore.QObject()
        setValue(o)
        self.assertEqual(o.property('test1'), ['Name'])



if __name__ == '__main__':
    unittest.main()


