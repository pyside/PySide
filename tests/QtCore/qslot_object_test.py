#!/usr/bin/python
import unittest
from PySide import QtCore

global qApp

class objTest(QtCore.QObject):

    def __init__(self, parent=None):
        QtCore.QObject.__init__(self, parent)

        self.ok = False

    def slot(self):
        global qApp
 
        self.ok = True
        qApp.quit()



class slotTest(unittest.TestCase):
    def quit_app(self):
        global qApp
       
        qApp.quit() 

    def testBasic(self):
        global qApp
        timer = QtCore.QTimer()
        timer.setInterval(100)

        my_obj = objTest()
        my_slot = QtCore.SLOT("slot()")
        QtCore.QObject.connect(timer, QtCore.SIGNAL("timeout()"), my_obj, my_slot)
        timer.start(100)

        QtCore.QTimer.singleShot(1000, self.quit_app)
        qApp.exec_()

        self.assert_(my_obj.ok)   


if __name__ == '__main__':
    global qApp
    qApp = QtCore.QCoreApplication([])
    unittest.main()
