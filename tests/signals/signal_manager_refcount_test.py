#!/usr/bin/python

from sys import getrefcount
import unittest
from PySide.QtCore import QObject, SIGNAL

class SignalManagerRefCount(unittest.TestCase):
    """Simple test case to check if the signal_manager is erroneously incrementing the object refcounter"""

    def testObjectRefcount(self):
        """Emission of QObject.destroyed() to a python slot"""
        def callback():
            pass
        obj = QObject()
        refcount = getrefcount(obj)
        QObject.connect(obj, SIGNAL('destroyed()'), callback)
        self.assertEqual(refcount, getrefcount(obj))
        QObject.disconnect(obj, SIGNAL('destroyed()'), callback)
        self.assertEqual(refcount, getrefcount(obj))

if __name__ == '__main__':
    unittest.main()

