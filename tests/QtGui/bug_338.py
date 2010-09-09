''' Test bug 338: http://bugs.openbossa.org/show_bug.cgi?id=338'''

import sys
import unittest
from PySide import QtCore,QtGui

class DiagramItem(QtGui.QGraphicsPolygonItem):
    def __init__(self, parent=None, scene=None):
        super(DiagramItem, self).__init__(parent, scene)

    def itemChange(self, change, value):
        return value


class BugTest(unittest.TestCase):
    def test(self):
        app = QtGui.QApplication(sys.argv)
        scene = QtGui.QGraphicsScene()
        item = DiagramItem()
        item2 = DiagramItem()
        #this cause segfault 
        scene.addItem(item)
        scene.addItem(item2)
  
