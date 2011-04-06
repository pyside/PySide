from PySide.QtCore import *
import unittest
import tempfile
import os

class TestBug724 (unittest.TestCase):

    def testIt(self):
        # creates a temporary file
        handle, self.filename = tempfile.mkstemp()
        os.write(handle, 'a')
        os.close(handle)

        engine = QAbstractFileEngine.create(self.filename)
        engine.open(QIODevice.ReadOnly)
        memory = engine.map(0, 1, QFile.NoOptions)
        self.assertEqual(len(memory), 1)
        self.assertEqual(memory[0], 'a')
        engine.unmap(memory)

if __name__ == '__main__':
    unittest.main()
