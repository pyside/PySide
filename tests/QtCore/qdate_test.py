#!/usr/bin/python
'''Test cases for QDate'''

import unittest

from PySide.QtCore import *

class TestQDate (unittest.TestCase):
    def testGetDate(self):
        date = QDate(2009, 22, 9)
        tuple_ = date.getDate()
        self.assertEquals(tuple, tuple_.__class__)
        (y, m, d) = tuple_
        self.assertEqual(date.year(), y)
        self.assertEqual(date.month(), m)
        self.assertEqual(date.day(), d)

    def testGetWeekNumber(self):
        date = QDate(2000, 1, 1)
        tuple_ = date.weekNumber()
        self.assertEquals(tuple, tuple_.__class__)
        (week, yearNumber) = tuple_
        self.assertEqual(week, 52)
        self.assertEqual(yearNumber, 1999)

    def testBooleanCast(self):
        today = QDate.currentDate()
        self.assertTrue(today)
        nodate = QDate()
        self.assertFalse(nodate)

if __name__ == '__main__':
    unittest.main()
