import unittest
import os
from helper import UsesQApplication

from PySide.QtGui import QWidget, QFrame, QPushButton
from PySide.QtUiTools import QUiLoader

#ugly workaround for work with ctest
file_path = [ "./test.ui", "./qtuitools/test.ui", "../tests/qtuitools/test.ui", "../../tests/qtuitools/test.ui" ]

def get_file_path():
    for path in file_path:
        if os.path.exists(path):
            return path
    return ""

class QUioaderTeste(UsesQApplication):
    def testLoadFile(self):
        widget = QWidget()

        file_path = get_file_path()
        self.assertTrue(file_path != "")

        QUiLoader.loadUi(file_path, widget)

        self.assertTrue("child_object" in dir(widget))
        self.assertTrue("grandson_object" in dir(widget.child_object))

        self.assertEqual(type(widget.child_object), QFrame)
        self.assertEqual(type(widget.child_object.grandson_object), QPushButton)

if __name__ == '__main__':
    unittest.main()

