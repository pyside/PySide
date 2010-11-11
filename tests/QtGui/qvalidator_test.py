from PySide.QtCore import *
from PySide.QtGui import *

import unittest
from helper import UsesQApplication

class MyValidator1(QValidator):
    def fixUp(self, input):
        return "fixed"

    def validate(self, input, pos):
        return (QValidator.Acceptable, "fixed", 1)

class MyValidator2(QValidator):
    def fixUp(self, input):
        return "fixed"

    def validate(self, input, pos):
        return (QValidator.Acceptable, "fixed")

class MyValidator3(QValidator):
    def fixUp(self, input):
        return "fixed"

    def validate(self, input, pos):
        return (QValidator.Acceptable,)

class MyValidator4(QValidator):
    def fixUp(self, input):
        return "fixed"

    def validate(self, input, pos):
        return QValidator.Acceptable

class QValidatorTest(UsesQApplication):
    def testValidator1(self):
        line = QLineEdit()
        line.setValidator(MyValidator1())
        line.show()
        line.setText("foo")

        QTimer.singleShot(0, line.close)
        self.app.exec_()

        self.assertEqual(line.text(), "fixed")
        self.assertEqual(line.cursorPosition(), 1)

    def testValidator2(self):
        line = QLineEdit()
        line.setValidator(MyValidator2())
        line.show()
        line.setText("foo")

        QTimer.singleShot(0, line.close)
        self.app.exec_()

        self.assertEqual(line.text(), "fixed")
        self.assertEqual(line.cursorPosition(), 3)

    def testValidator3(self):
        line = QLineEdit()
        line.setValidator(MyValidator3())
        line.show()
        line.setText("foo")

        QTimer.singleShot(0, line.close)
        self.app.exec_()

        self.assertEqual(line.text(), "foo")
        self.assertEqual(line.cursorPosition(), 3)

    def testValidator4(self):
        line = QLineEdit()
        line.setValidator(MyValidator4())
        line.show()
        line.setText("foo")

        QTimer.singleShot(0, line.close)
        self.app.exec_()

        self.assertEqual(line.text(), "foo")
        self.assertEqual(line.cursorPosition(), 3)

if __name__ == '__main__':
    unittest.main()
