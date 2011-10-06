'''Test cases for PySide API2 support'''


import unittest
import sys

from PySide.QtGui import QWidget, QIntValidator, QSpinBox, QValidator, QApplication

from helper import UsesQApplication

class WidgetValidatorQInt(QWidget, QIntValidator):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        QIntValidator.__init__(self, parent)

class WidgetValidatorQSpinBox(QSpinBox):
    def __init__(self, parent=None):
        QSpinBox.__init__(self, parent)

    def fixup(self, text):
        print("It was called!")

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
        self.assertEqual(obj.value(), 1)

class QClipboardTest(UsesQApplication):

    def testQClipboard(self):
        #skip this test on MacOS because the clipboard is not available during the ssh session
        #this cause problems in the buildbot
        if sys.platform == 'darwin':
            return
        clip = QApplication.clipboard()
        clip.setText("Testing this thing!")

        text, subtype = clip.text("")
        self.assertEqual(subtype, "plain")
        self.assertEqual(text, "Testing this thing!")

if __name__ == '__main__':
    unittest.main()
