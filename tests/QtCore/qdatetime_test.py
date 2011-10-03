import unittest
import datetime

from PySide.QtCore import QDateTime, QDate, QTime

class TestQDate (unittest.TestCase):
    def testDateConversion(self):
        dateTime = QDateTime(QDate(2011, 5, 17), QTime(11, 1, 14, 15))
        dateTimePy = QDateTime(datetime.date(2011, 5, 17), datetime.time(11, 1, 14, 15000))
        self.assertEqual(dateTime, dateTimePy)

    def testDateTimeConversion(self):
        dateTime = QDateTime(QDate(2011, 5, 17), QTime(11, 1, 14, 15))
        dateTimePy = QDateTime(datetime.datetime(2011, 5, 17, 11, 1, 14, 15000))
        self.assertEqual(dateTime, dateTimePy)

    def testDateTimeNow(self):
        py = datetime.datetime.now()
        qt = QDateTime(py)
        self.assertEqual(qt, py)

if __name__ == '__main__':
    unittest.main()
