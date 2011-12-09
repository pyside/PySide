''' unit test for BUG #1063 '''

import unittest
import tempfile
from PySide import QtCore
import os
import py3kcompat as py3k

class QTextStreamTestCase(unittest.TestCase):
    def setUp(self):
        self.temp_file = tempfile.NamedTemporaryFile(delete=False)
        self.temp_file.close()
        self.f = QtCore.QFile(self.temp_file.name)
        self.f.open(QtCore.QIODevice.WriteOnly)
        self.strings = (py3k.unicode_('foo'), py3k.unicode_('bar'))
        self.stream = QtCore.QTextStream(self.f)

    def testIt(self):
        for s in self.strings:
            self.stream << s

        self.f.close()

        # make sure we didn't get an empty file
        self.assertNotEqual(QtCore.QFile(self.temp_file.name).size(), 0)

        os.unlink(self.temp_file.name)

if __name__ == "__main__":
    unittest.main()
