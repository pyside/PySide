#!/usr/bin/python
'''Unit tests for QGLBuffer'''

import unittest

from PySide.QtCore import QByteArray
from PySide.QtOpenGL import QGLBuffer, QGLWidget

from helper import UsesQApplication

class QGLBufferTest(UsesQApplication):
    def testIt(self):
        w = QGLWidget()
        w.makeCurrent()

        b = QGLBuffer()
        b.setUsagePattern(QGLBuffer.DynamicDraw)

        self.assert_(b.create())
        self.assert_(b.bufferId() != 0)
        self.assert_(b.bind())

        data = QByteArray("12345")
        b.allocate(data)
        self.assertEqual(b.size(), data.size())

        m = b.map(QGLBuffer.ReadOnly)
        if m:
            self.assertEqual(m, buffer(data.data()))
            b.unmap()

            m = b.map(QGLBuffer.ReadWrite)
            m[3] = 'A'
            b.unmap()
            result, rdata = b.read(3, 1)
            self.assertTrue(result)
            self.assertEqual('A', rdata.data())
        else:
            print " memory mapping is not possible in this OpenGL implementation."
        b.release()

if __name__ == '__main__':
    unittest.main()
