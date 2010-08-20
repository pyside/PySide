#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide.QtCore import QObject, QCoreApplication, QTimeLine, Signal, Slot
from helper import UsesQCoreApplication

class ExtQObject(QObject):
    signalbetween = Signal('qreal')

    def __init__(self):
        QObject.__init__(self)
        self.counter = 0

    @Slot('qreal')
    def foo(self, value):
        self.counter += 1


class SignaltoSignalTest(UsesQCoreApplication):

    def setUp(self):
        UsesQCoreApplication.setUp(self)
        self.receiver = ExtQObject()
        self.timeline = QTimeLine(100)

    def tearDown(self):
        del self.timeline
        del self.receiver
        UsesQCoreApplication.tearDown(self)

    def testSignaltoSignal(self):
        self.timeline.setUpdateInterval(10)

        self.timeline.finished.connect(self.app.quit)

        self.timeline.valueChanged.connect(self.receiver.signalbetween)
        self.receiver.signalbetween.connect(self.receiver.foo)

        self.timeline.start()

        self.app.exec_()

        self.assert_(self.receiver.counter > 1)


if __name__ == '__main__':
    unittest.main()

