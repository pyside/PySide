#!/usr/bin/python
import unittest
from PySide.QtCore import QDate, QDateTime, QTime, QUrl

class HashTest(unittest.TestCase):
    def testInsert(self):
        myHash = {}
        qdate = QDate.currentDate()
        qdatetime = QDateTime.currentDateTime()
        qtime = QTime.currentTime()
        qurl = QUrl("http://www.pyside.org")

        myHash[qdate] = "QDate"
        myHash[qdatetime] = "QDateTime"
        myHash[qtime] = "QTime"
        myHash[qurl] = "QUrl"

        self.assertEqual(myHash[qdate], "QDate")
        self.assertEqual(myHash[qdatetime], "QDateTime")
        self.assertEqual(myHash[qtime], "QTime")
        self.assertEqual(myHash[qurl], "QUrl")


if __name__ == '__main__':
    unittest.main()
