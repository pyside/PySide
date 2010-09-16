#!/usr/bin/python
'''Test cases for QObject protected methods'''

import unittest

from PySide.QtCore import QObject, QThread, SIGNAL

class Dummy(QObject):
    '''Dummy class'''
    pass

class QObjectReceivers(unittest.TestCase):
    '''Test case for QObject.receivers()'''

    def cb(self, *args):
        #Dummy callback
        pass

    def testQObjectReceiversExtern(self):
        #QObject.receivers() - Protected method external access

        obj = Dummy()
        self.assertEqual(obj.receivers(SIGNAL("destroyed()")), 0)

        QObject.connect(obj, SIGNAL("destroyed()"), self.cb)
        self.assertEqual(obj.receivers(SIGNAL("destroyed()")), 1)

    def testQThreadReceiversExtern(self):
        #QThread.receivers() - Inherited protected method

        obj = QThread()
        self.assertEqual(obj.receivers(SIGNAL('destroyed()')), 0)
        QObject.connect(obj, SIGNAL("destroyed()"), self.cb)
        self.assertEqual(obj.receivers(SIGNAL("destroyed()")), 1)


if __name__ == '__main__':
    unittest.main()
