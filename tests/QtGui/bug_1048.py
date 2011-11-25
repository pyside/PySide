from PySide import QtGui

a = QtGui.QApplication([])

w = QtGui.QWidget()
l = QtGui.QGridLayout(w)

l.itemAtPosition(0, 0)
