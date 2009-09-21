#!/usr/bin/env python

'''Connecting lambda to signals'''

import unittest

from PySide.QtCore import QObject, SIGNAL
from PySide.QtGui import QApplication, QSpinBox, QPushButton

from helper import UsesQApplication

class Dummy(QObject):
    def __init__(self, *args):
        super(Dummy, self).__init__(*args)

class BasicCase(unittest.TestCase):

    def testSimplePythonSignalNoArgs(self):
        #Connecting a lambda to a simple python signal without arguments
        obj = Dummy()
        QObject.connect(obj, SIGNAL('foo()'), lambda : setattr(obj, 'called', True))
        obj.emit(SIGNAL('foo()'))
        self.assert_(obj.called)

    def testSimplePythonSignal(self):
        #Connecting a lambda to a simple python signal witharguments
        obj = Dummy()
        arg = 42
        QObject.connect(obj, SIGNAL('foo(int)'), lambda x : setattr(obj, 'arg', 42))
        obj.emit(SIGNAL('foo(int)'), arg)
        self.assertEqual(obj.arg, arg)

class QtSigLambda(UsesQApplication):

    qapplication = True

    def testButton(self):
        #Connecting a lambda to a QPushButton.clicked()
        obj = QPushButton('label')
        QObject.connect(obj, SIGNAL('clicked()'), lambda : setattr(obj, 'called', True))
        obj.click()
        self.assert_(obj.called)

    def testSpinButton(self):
        #Connecting a lambda to a QPushButton.clicked()
        obj = QSpinBox()
        arg = 444
        QObject.connect(obj, SIGNAL('valueChanged(int)'), lambda x: setattr(obj, 'arg', 444))
        obj.setValue(444)
        self.assertEqual(obj.arg, arg)

if __name__ == '__main__':
    unittest.main()
