from PySide.QtCore import QAbstractFileEngine, QIODevice, QFile
import unittest
import tempfile
import os
import py3kcompat as py3k

class TestBug724 (unittest.TestCase):

    def testIt(self):
        # creates a temporary file
        handle, self.filename = tempfile.mkstemp()
        os.write(handle, py3k.b('a'))
        os.close(handle)

        engine = QAbstractFileEngine.create(self.filename)
        engine.open(QIODevice.ReadOnly)
        memory = engine.map(0, 1, QFile.NoOptions)
        self.assertEqual(len(memory), 1)
        self.assertEqual(memory[0], py3k.b('a'))
        engine.unmap(memory)

if __name__ == '__main__':
    unittest.main()
