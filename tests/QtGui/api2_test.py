'''Test cases for PySide API2 support'''


import unittest

from PySide.QtCore import QObject
from PySide.QtGui import *

from helper import UsesQApplication

class WidgetValidatorQInt(QWidget, QIntValidator):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        QIntValidator.__init__(self, parent)

class WidgetValidatorQSpinBox(QSpinBox):
    def __init__(self, parent=None):
        QSpinBox.__init__(self, parent)

    def fixup(self, text):
        print "It was called!"

class DoubleQObjectInheritanceTest(UsesQApplication):

    def testDouble(self):
        '''Double inheritance from QObject classes'''

        obj = WidgetValidatorQInt()

        #QIntValidator methods
        state, string, number = obj.validate('Test', 0)
        self.assertEqual(state, QValidator.Invalid)
        state, string, number = obj.validate('33', 0)
        self.assertEqual(state, QValidator.Acceptable)

    def testQSpinBox(self):
        obj = WidgetValidatorQSpinBox()

        obj.setRange(1, 10)
        obj.setValue(0)
        print "Value:", obj.value()

class QClipboardTest(UsesQApplication):

    def testQClipboard(self):
        clip = QClipboard()
        clip.setText("Testing this thing!")

        text, subtype = clip.text("")
        self.assertEqual(subtype, "plain")
        self.assertEqual(text, "Testing this thing!")

#class QFileDialog(UsesQApplication):
#
#    def testQFileDialog(self):
#        string, filtr = QFileDialog.getOpenFileName()
#        print string, filtr

if __name__ == '__main__':
    unittest.main()
