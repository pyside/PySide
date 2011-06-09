import unittest
from helper import UsesQApplication
from PySide.QtGui import QLineEdit, QValidator, QIntValidator

'''Bug #871 - http://bugs.pyside.org/show_bug.cgi?id=871'''


class BlankIntValidator(QIntValidator):
    def validate(self,input,pos):
        if input == '':
            return QValidator.Acceptable, input, pos
        else:
            return QIntValidator.validate(self,input,pos)


class Bug871Test(UsesQApplication):
    def testWithoutValidator(self):
        edit = QLineEdit()
        self.assertEqual(edit.text(), '')
        edit.insert('1')
        self.assertEqual(edit.text(), '1')
        edit.insert('a')
        self.assertEqual(edit.text(), '1a')
        edit.insert('2')
        self.assertEqual(edit.text(), '1a2')

    def testWithIntValidator(self):
        edit = QLineEdit()
        edit.setValidator(BlankIntValidator(edit))
        self.assertEqual(edit.text(), '')
        edit.insert('1')
        self.assertEqual(edit.text(), '1')
        edit.insert('a')
        self.assertEqual(edit.text(), '1')
        edit.insert('2')
        self.assertEqual(edit.text(), '12')


if __name__ == "__main__":
   unittest.main()

