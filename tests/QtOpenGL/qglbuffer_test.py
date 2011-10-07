#!/usr/bin/python
'''Unit tests for QGLBuffer'''

import unittest

from PySide.QtCore import QByteArray
from PySide.QtOpenGL import QGLBuffer, QGLWidget
import py3kcompat as py3k
from helper import UsesQApplication

class QGLBufferTest(UsesQApplication):
    def testIt(self):
        w = QGLWidget()
        w.makeCurrent()

        b = QGLBuffer()
        b.setUsagePattern(QGLBuffer.DynamicDraw)

        self.assertTrue(b.create())
        self.assertTrue(b.bufferId() != 0)
        self.assertTrue(b.bind())

        data = QByteArray("12345")
        b.allocate(data)
        self.assertEqual(b.size(), data.size())

        m = b.map(QGLBuffer.ReadOnly)
        if m:
            self.assertEqual(m, py3k.buffer(py3k.b(data.data())))
            b.unmap()

            m = b.map(QGLBuffer.ReadWrite)
            m[3] = py3k.b('A')
            b.unmap()
            result, rdata = b.read(3, 1)
            self.assertTrue(result)
            self.assertEqual(py3k.b('A'), rdata.data())
        else:
            print(" memory mapping is not possible in this OpenGL implementation.")
        b.release()

if __name__ == '__main__':
    unittest.main()
