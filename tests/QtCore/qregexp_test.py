#!/usr/bin/python

import unittest
from PySide.QtCore import QRegExp

class QRegExpTest(unittest.TestCase):

    def testReplace1(self):
        re = QRegExp('a[mn]')
        string = re.replace('Banana', 'ox')
        self.assertEqual(string, 'Boxoxa')

    def testReplace2(self):
        re = QRegExp('<i>([^<]*)</i>')
        string = re.replace('A <i>bon mot</i>.', '\\emph{\\1}')
        self.assertEqual(string, 'A \\emph{bon mot}.')

if __name__ == '__main__':
    unittest.main()

