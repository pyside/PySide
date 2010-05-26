#!/usr/bin/python
'''Unit tests for QGLBuffer''

import unittest

from PySide.QtCore import QByteArray
from PySide.QtOpenGL import QGLBuffer, QGLWidget

from helper import UsesQApplication

class QGLBufferTest(UsesQApplication):
    def usageCheck(self, t):
        w = QGLWidget()
        w.makeCurrent()

        b = QGLBuffer(t)
        self.assertEqual(b.usagePattern(), QGLBuffer.StaticDraw)
        b.setUsagePattern(QGLBuffer.DynamicDraw)

        self.assert_(b.create())
        self.assert_(b.bufferId() != 0)
        self.assert_(b.bind())

        data = QByteArray("12345")
        b.allocate(data)
        self.assertEqual(b.size(), data.size())

        m = b.map(QGLBuffer.ReadOnly)
        self.assertEqual(m.data(), data.data())
        b.unmap()

        other_data = QByteArray("67")
        b.write(0, other_data)
        m = b.map(QGLBuffer.ReadOnly)
        self.assertEqual(m.mid(0, other_data.size()).data(), other_data.data())
        b.unmap()

        result, rdata = b.read(0, other_data.size())
        print result, rdata
        self.assert_(result)
        self.assertEqual(other_data.data(), rdata.data())

        b.release()

    def testUsage(self):
        self.usageCheck(QGLBuffer.IndexBuffer)

if __name__ == '__main__':
    unittest.main()
