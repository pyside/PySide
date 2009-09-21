#!/usr/bin/python
'''Test cases for QtCore.QEvent'''

import unittest

from PySide.QtCore import QEvent

class QEventTypeFlag(unittest.TestCase):
    '''Test case for usage of QEvent.Type flags'''

    def testFlagAccess(self):
        #QEvent.Type flags usage

        event = QEvent(QEvent.Timer)
        self.assertEqual(event.type(), QEvent.Timer)

        event = QEvent(QEvent.Close)
        self.assertEqual(event.type(), QEvent.Close)

        event = QEvent(QEvent.IconTextChange)
        self.assertEqual(event.type(), QEvent.IconTextChange)

if __name__ == '__main__':
    unittest.main()
