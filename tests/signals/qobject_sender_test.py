#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QObject.sender()'''

import unittest
from PySide.QtCore import *
from helper import UsesQCoreApplication

class ExtQTimer(QTimer):
    def __init__(self):
        QTimer.__init__(self)

class Receiver(QObject):
    def __init__(self):
        QObject.__init__(self)
        self.the_sender = None

    def callback(self):
        self.the_sender = self.sender()
        if QCoreApplication.instance():
            QCoreApplication.instance().exit()

class ObjectSenderTest(unittest.TestCase):
    '''Test case for QObject.sender() method.'''

    def testSenderPythonSignal(self):
        sender = QObject()
        recv = Receiver()
        QObject.connect(sender, SIGNAL('foo()'), recv.callback)
        sender.emit(SIGNAL('foo()'))
        self.assertEquals(sender, recv.the_sender)

class ObjectSenderCheckOnReceiverTest(unittest.TestCase):
    '''Test case for QObject.sender() method, this one tests the equality on the Receiver object.'''

    def testSenderPythonSignal(self):
        sender = QObject()
        recv = Receiver()
        QObject.connect(sender, SIGNAL('foo()'), recv.callback)
        sender.emit(SIGNAL('foo()'))
        self.assertEquals(sender, recv.the_sender)

class ObjectSenderWithQAppTest(UsesQCoreApplication):
    '''Test case for QObject.sender() method with QApplication.'''

    def testSenderCppSignal(self):
        sender = QTimer()
        sender.setObjectName('foo')
        recv = Receiver()
        QObject.connect(sender, SIGNAL('timeout()'), recv.callback)
        sender.start(10)
        self.app.exec_()
        self.assertEquals(sender, recv.the_sender)

    def testSenderCppSignalSingleShotTimer(self):
        recv = Receiver()
        QTimer.singleShot(10, recv.callback)
        self.app.exec_()
        self.assertTrue(isinstance(recv.the_sender, QObject))

    def testSenderCppSignalWithPythonExtendedClass(self):
        sender = ExtQTimer()
        recv = Receiver()
        QObject.connect(sender, SIGNAL('timeout()'), recv.callback)
        sender.start(10)
        self.app.exec_()
        self.assertEquals(sender, recv.the_sender)

class ObjectSenderWithQAppCheckOnReceiverTest(UsesQCoreApplication):
    '''Test case for QObject.sender() method with QApplication.'''

    def testSenderCppSignal(self):
        sender = QTimer()
        sender.setObjectName('foo')
        recv = Receiver()
        QObject.connect(sender, SIGNAL('timeout()'), recv.callback)
        sender.start(10)
        self.app.exec_()
        self.assertEquals(sender, recv.the_sender)

    def testSenderCppSignalWithPythonExtendedClass(self):
        sender = ExtQTimer()
        recv = Receiver()
        QObject.connect(sender, SIGNAL('timeout()'), recv.callback)
        sender.start(10)
        self.app.exec_()
        self.assertEquals(sender, recv.the_sender)

if __name__ == '__main__':
    unittest.main()

