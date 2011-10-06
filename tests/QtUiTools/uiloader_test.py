import unittest
import os
from helper import UsesQApplication

from PySide.QtGui import QWidget
from PySide.QtUiTools import QUiLoader

def get_file_path():
    for path in file_path:
        if os.path.exists(path):
            return path
    return ""

class QUioaderTeste(UsesQApplication):
    def testLoadFile(self):
        filePath = os.path.join(os.path.dirname(__file__), 'test.ui')
        loader = QUiLoader()
        parent = QWidget()
        w = loader.load(filePath, parent)
        self.assertNotEqual(w, None)

        self.assertEqual(len(parent.children()), 1)

        child = w.findChild(QWidget, "child_object")
        self.assertNotEqual(child, None)
        self.assertEqual(w.findChild(QWidget, "grandson_object"), child.findChild(QWidget, "grandson_object"))

    def testLoadFileUnicodeFilePath(self):
        filePath = str(os.path.join(os.path.dirname(__file__), 'test.ui'))
        loader = QUiLoader()
        parent = QWidget()
        w = loader.load(filePath, parent)
        self.assertNotEqual(w, None)

        self.assertEqual(len(parent.children()), 1)

        child = w.findChild(QWidget, "child_object")
        self.assertNotEqual(child, None)
        self.assertEqual(w.findChild(QWidget, "grandson_object"), child.findChild(QWidget, "grandson_object"))

if __name__ == '__main__':
    unittest.main()

