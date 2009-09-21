
''' Test cases related to QGraphicsItem and subclasses'''

import unittest

from PySide.QtGui import QGraphicsScene, QPolygonF, QColor, QBrush

from helper import UsesQApplication

class QColorOnSetBrush(UsesQApplication):
    '''Test case for passing a QColor directly to setBrush'''

    def setUp(self):
        #Acquire resources
        super(QColorOnSetBrush, self).setUp()

        self.scene = QGraphicsScene()
        poly = QPolygonF()
        self.item = self.scene.addPolygon(poly)
        self.color = QColor('black')

    def tearDown(self):
        #Release resources
        del self.color
        del self.item
        del self.scene
        super(QColorOnSetBrush, self).tearDown()

    def testQColor(self):
        #QGraphicsAbstractShapeItem.setBrush(QColor)
        self.item.setBrush(self.color)
        self.assertEqual(QBrush(self.color), self.item.brush())

if __name__ == '__main__':
    unittest.main()
