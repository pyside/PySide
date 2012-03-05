#!/usr/bin/python
'''Test cases for QLineF'''

import unittest
import datetime

from PySide.QtCore import QTime, QDateTime, QDate

class TestDateTimeConversions (unittest.TestCase):
    def testQDate(self):
        date = datetime.date(2010, 4, 23)
        other = QDate(date)
        self.assertEqual(date.year, other.year())
        self.assertEqual(date.month, other.month())
        self.assertEqual(date.day, other.day())

        self.assertEqual(date, other.toPython())

    def testQTime(self):
        time = datetime.time(11, 14, 0, 1000)
        other = QTime(time)
        self.assertEqual(time.hour, other.hour())
        self.assertEqual(time.minute, other.minute())
        self.assertEqual(time.second, other.second())
        self.assertEqual(time.microsecond/1000, other.msec())

        self.assertEqual(time, other.toPython())

    def testQDateTime(self):
        dateTime = datetime.datetime(2010, 4, 23, 11, 14, 0, 1000)
        other = QDateTime(dateTime)

        otherDate = other.date()
        self.assertEqual(dateTime.year, otherDate.year())
        self.assertEqual(dateTime.month, otherDate.month())
        self.assertEqual(dateTime.day, otherDate.day())

        otherTime = other.time()
        self.assertEqual(dateTime.hour, otherTime.hour())
        self.assertEqual(dateTime.minute, otherTime.minute())
        self.assertEqual(dateTime.second, otherTime.second())
        self.assertEqual(dateTime.microsecond/1000, otherTime.msec())

        self.assertEqual(dateTime, other.toPython())

    def testQDateTime6arg(self):
        dateTime = datetime.datetime(2010, 4, 23, 11, 14, 7)
        other = QDateTime(dateTime)

        otherDate = other.date()
        self.assertEqual(dateTime.year, otherDate.year())
        self.assertEqual(dateTime.month, otherDate.month())
        self.assertEqual(dateTime.day, otherDate.day())

        otherTime = other.time()
        self.assertEqual(dateTime.hour, otherTime.hour())
        self.assertEqual(dateTime.minute, otherTime.minute())
        self.assertEqual(dateTime.second, otherTime.second())
        self.assertEqual(dateTime.microsecond/1000, otherTime.msec())

        self.assertEqual(dateTime, other.toPython())

if __name__ == '__main__':
    unittest.main()
