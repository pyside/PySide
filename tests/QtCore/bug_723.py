import unittest
from PySide.QtCore import *

class MyFileEngine (QAbstractFileEngine):

    def __init__(self):
        QAbstractFileEngine.__init__(self)
        self.contents = "Foo \0bar for the win!"
        self.pos = 0

    def open(self, mode):
        return True

    def read(self, maxlen):
        print("Reading... to return ", self.contents[self.pos:maxlen])

        if self.pos > len(self.contents):
            return -1

        res = self.contents[self.pos:maxlen]
        self.pos += len(res)
        return res

    def readLine(self, maxlen):
        return self.contents[self.pos:maxlen]

class MyFileEngineHandler (QAbstractFileEngineHandler):

    def create(self, fileName):
        if fileName.startswith("foo:/"):
            return MyFileEngine()
        return None


class TestBug723 (unittest.TestCase):

    def testIt(self):
        fh = MyFileEngineHandler()

        f = QFile("foo:/bar")

        print(type(QFile.ReadOnly))
        v = (QFile.ReadOnly | QFile.Text)
        print(type(v))

        """
        assert(f.open(QFile.ReadOnly | QFile.Text))
        contents = f.readAll()
        self.assertEqual(contents, "Foo \0bar for the win!")
        f.close()
        """


if __name__ == '__main__':
    unittest.main()
