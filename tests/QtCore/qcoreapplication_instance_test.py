#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QCoreApplication.instance static method'''

import unittest

from PySide.QtCore import QCoreApplication

class QCoreApplicationInstanceTest(unittest.TestCase):
    '''Test cases for QCoreApplication.instance static method'''

    def testQCoreApplicationInstance(self):
        #Tests QCoreApplication.instance()
        self.assertEqual(QCoreApplication.instance(), None)
        app = QCoreApplication([])
        self.assertEqual(QCoreApplication.instance(), app)

if __name__ == '__main__':
    unittest.main()

