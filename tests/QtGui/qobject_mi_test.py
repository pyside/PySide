'''Test cases for multiple inheritance from 2 QObjects'''

import unittest

from PySide.QtCore import QObject
from PySide.QtGui import *

from helper import UsesQApplication

class WidgetValidator(QWidget, QIntValidator):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        QIntValidator.__init__(self, parent)


class DoubleQObjectInheritanceTest(UsesQApplication):

    def testDouble(self):
        '''Double inheritance from QObject classes'''

        obj = WidgetValidator()

        #QObject methods
        obj.setObjectName('aaaa')
        self.assertEqual(obj.objectName(), 'aaaa')

        #QWidget methods
        obj.setVisible(False)
        self.assertFalse(obj.isVisible())

        #QIntValidator methods
        state, string, number = obj.validate('aaaa', 0)
        self.assertEqual(state, QValidator.Invalid)
        state, string, number = obj.validate('33', 0)
        self.assertEqual(state, QValidator.Acceptable)


if __name__ == '__main__':
    unittest.main()
