
'''Test cases for Reference count when the object is created in c++ side'''

import unittest

import sys
import weakref
import gc


from PySide.QtCore import Qt, QPointF
from PySide.QtGui import QApplication, QGraphicsScene, QGraphicsRectItem, QPolygonF, QGraphicsPolygonItem, QGraphicsRectItem

from helper import UsesQApplication

destroyedRect = False
destroyedPol = False

def rect_del(o):
    global destroyedRect
    destroyedRect = True

def pol_del(o):
    global destroyedPol
    destroyedPol = True

class ReferenceCount(UsesQApplication):

    def setUp(self):
        super(ReferenceCount, self).setUp()
        self.scene = QGraphicsScene()

    def tearDown(self):
        super(ReferenceCount, self).tearDown()

    def beforeTest(self):
        points = [QPointF(0, 0), QPointF(100, 100), QPointF(0, 100)]
        pol = self.scene.addPolygon(QPolygonF(points))
        self.assert_(isinstance(pol, QGraphicsPolygonItem))
        self.wrp = weakref.ref(pol, pol_del)

        #refcount need be 3 because one ref for QGraphicsScene, and one to rect obj
        self.assertEqual(sys.getrefcount(pol), 3)

    def testReferenceCount(self):
        global destroyedRect
        global destroyedPol

        self.beforeTest()
        
        rect = self.scene.addRect(10.0, 10.0, 10.0, 10.0)
        self.assert_(isinstance(rect, QGraphicsRectItem))

        self.wrr = weakref.ref(rect, rect_del)

        #refcount need be 3 because one ref for QGraphicsScene, and one to rect obj
        self.assertEqual(sys.getrefcount(rect), 3)

        del rect
        #not destroyed because one ref continue in QGraphicsScene
        self.assertEqual(destroyedRect, False)
        self.assertEqual(destroyedPol, False)

        del self.scene

        #QGraphicsScene was destroyed and this destroy internal ref to rect
        self.assertEqual(destroyedRect, True)
        self.assertEqual(destroyedPol, True)

if __name__ == '__main__':
    unittest.main()
