#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide.QtCore import QObject, QCoreApplication, QTimeLine, Slot
from helper import UsesQCoreApplication

class ExtQObject(QObject):

    def __init__(self):
        QObject.__init__(self)
        self.counter = 0

    @Slot('qreal')
    def foo(self, value):
        self.counter += 1


class UserSlotTest(UsesQCoreApplication):

    def setUp(self):
        UsesQCoreApplication.setUp(self)
        self.receiver = ExtQObject()
        self.timeline = QTimeLine(100)

    def tearDown(self):
        del self.timeline
        del self.receiver
        UsesQCoreApplication.tearDown(self)

    def testUserSlot(self):
        self.timeline.setUpdateInterval(10)

        self.timeline.finished.connect(self.app.quit)

        self.timeline.valueChanged.connect(self.receiver.foo)
        self.timeline.start()

        self.app.exec_()

        self.assert_(self.receiver.counter > 1)


if __name__ == '__main__':
    unittest.main()

