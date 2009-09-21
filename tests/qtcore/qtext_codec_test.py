import gc
import unittest

from PySide.QtCore import QTextCodec

class TestCodecGetters(unittest.TestCase):

    def testCodecsNames(self):
        for codec_name in QTextCodec.availableCodecs():
            codec = QTextCodec.codecForName(codec_name)
            self.assert_(type(codec), QTextCodec)

    def testCodecsMibs(self):
        for codec_num in QTextCodec.availableMibs():
            codec = QTextCodec.codecForMib(codec_num)
            self.assert_(type(codec), QTextCodec)


if __name__ == '__main__':
        unittest.main()
