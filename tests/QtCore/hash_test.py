#!/usr/bin/python
import unittest
from PySide.QtCore import QDate, QDateTime, QTime, QUrl
from PySide.QtCore import QLine, QPoint, QRect, QSize

class HashTest(unittest.TestCase):
    def testInsert(self):
        myHash = {}
        qdate = QDate.currentDate()
        qdatetime = QDateTime.currentDateTime()
        qtime = QTime.currentTime()
        qurl = QUrl("http://www.pyside.org")
        qpoint = QPoint(12, 42)

        myHash[qdate] = "QDate"
        myHash[qdatetime] = "QDateTime"
        myHash[qtime] = "QTime"
        myHash[qurl] = "QUrl"
        myHash[qpoint] = "QPoint"

        self.assertEqual(myHash[qdate], "QDate")
        self.assertEqual(myHash[qdatetime], "QDateTime")
        self.assertEqual(myHash[qtime], "QTime")
        self.assertEqual(myHash[qurl], "QUrl")
        self.assertEqual(myHash[qpoint], "QPoint")

    def testQPointHash(self):
        p1 = QPoint(12, 34)
        p2 = QPoint(12, 34)
        self.assertFalse(p1 is p2)
        self.assertEqual(p1, p2)
        self.assertEqual(hash(p1), hash(p2))

    def testQSizeHash(self):
        s1 = QSize(12, 34)
        s2 = QSize(12, 34)
        self.assertFalse(s1 is s2)
        self.assertEqual(s1, s2)
        self.assertEqual(hash(s1), hash(s2))

    def testQRectHash(self):
        r1 = QRect(12, 34, 56, 78)
        r2 = QRect(12, 34, 56, 78)
        self.assertFalse(r1 is r2)
        self.assertEqual(r1, r2)
        self.assertEqual(hash(r1), hash(r2))

    def testQLineHash(self):
        l1 = QLine(12, 34, 56, 78)
        l2 = QLine(12, 34, 56, 78)
        self.assertFalse(l1 is l2)
        self.assertEqual(l1, l2)
        self.assertEqual(hash(l1), hash(l2))

if __name__ == '__main__':
    unittest.main()

