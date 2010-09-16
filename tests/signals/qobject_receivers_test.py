# -*- coding: utf-8 -*-

''' Test case for QObject.receivers()'''

import unittest
from PySide.QtCore import *

def cute_slot():
    pass

class TestQObjectReceivers(unittest.TestCase):
    '''Test case for QObject::receivers'''

    def testBasic(self):
        sender = QObject()
        receiver1 = QObject()
        receiver2 = QObject()
        self.assertEqual(sender.receivers(SIGNAL("")), 0)
        sender.connect(sender, SIGNAL("destroyed()"), receiver1, SLOT("deleteLater()"))
        self.assertEqual(sender.receivers(SIGNAL("destroyed()")), 1)
        sender.connect(sender, SIGNAL("destroyed()"), receiver2, SLOT("deleteLater()"))
        self.assertEqual(sender.receivers(SIGNAL("destroyed()")), 2)
        sender.disconnect(sender, SIGNAL("destroyed()"), receiver2, SLOT("deleteLater()"))
        self.assertEqual(sender.receivers(SIGNAL("destroyed()")), 1)
        del receiver2
        del receiver1
        del sender

    def testPySlots(self):
        sender = QObject()
        receiver = QObject()
        sender.connect(sender, SIGNAL("destroyed()"), cute_slot)
        self.assertEqual(sender.receivers(SIGNAL("destroyed( )")), 1)
        sender.connect(sender, SIGNAL("destroyed()"), receiver, SLOT("deleteLater()"))
        self.assertEqual(sender.receivers(SIGNAL("destroyed()")), 2)
        del sender
        del receiver

    def testPySignals(self):
        sender = QObject()
        receiver = QObject()
        sender.connect(sender, SIGNAL("some_dynamic_signal()"), cute_slot)
        self.assertEqual(sender.receivers(SIGNAL("some_dynamic_signal(  )")), 1)
        sender.connect(sender, SIGNAL("some_dynamic_signal()"), receiver, SLOT("deleteLater()"))
        self.assertEqual(sender.receivers(SIGNAL("some_dynamic_signal(  )")), 2)

if __name__ == '__main__':
    unittest.main()
