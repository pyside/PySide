''' unit test for BUG #1077 '''

from PySide import QtCore, QtGui
import time

class Highlighter(QtGui.QSyntaxHighlighter):
    def __init__(self, parent, mode):
        QtGui.QSyntaxHighlighter.__init__(self, parent)
        self.tstamp = time.time()

if __name__ == "__main__":
    app = QtGui.QApplication([])
    python = QtGui.QTextEdit()
    python.setWindowTitle("python")
    hl = Highlighter(python.document(), "python")
    python.show()
    text = hl.document()
