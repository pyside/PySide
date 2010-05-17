#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide.QtCore import QCoreApplication, QTimeLine
from helper import UsesQCoreApplication

class NativeSignalsTest(UsesQCoreApplication):

    def setUp(self):
        UsesQCoreApplication.setUp(self)
        self.called = False
        self.timeline = QTimeLine(100)

    def tearDown(self):
        del self.called
        del self.timeline
        UsesQCoreApplication.tearDown(self)

    def testSignalWithIntArgument(self):

        def valueChangedSlot(value):
            self.called = True
            self.assertEqual(type(value), float)
            self.app.quit()

        self.timeline.valueChanged.connect(valueChangedSlot)
        self.timeline.start()

        self.app.exec_()
        self.assert_(self.called)

    def testSignalWithoutArguments(self):

        def finishedSlot():
            self.called = True
            self.app.quit()

        self.timeline.finished.connect(finishedSlot)
        self.timeline.start()

        self.app.exec_()
        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()

