import unittest
import datetime

from PySide.QtCore import QDateTime, QDate, QTime

class TestQDate (unittest.TestCase):
    def testDateConversion(self):
        dateTime = QDateTime(QDate(2011, 05, 17), QTime(11, 01, 14, 15))
        dateTimePy = QDateTime(datetime.date(2011, 05, 17), datetime.time(11, 01, 14, 15))
        self.assertEqual(dateTime, dateTimePy)

    def testDateTimeConversion(self):
        dateTime = QDateTime(QDate(2011, 05, 17), QTime(11, 01, 14, 15))
        dateTimePy = QDateTime(datetime.datetime(2011, 05, 17, 11, 01, 14, 15))
        self.assertEqual(dateTime, dateTimePy)

if __name__ == '__main__':
    unittest.main()
