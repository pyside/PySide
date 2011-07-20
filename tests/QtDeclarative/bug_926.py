import sys
import unittest
from helper import adjust_filename
from PySide.QtCore import *
from PySide.QtGui import *
from PySide.QtDeclarative import *

class MyClass (QObject):

    def __init__(self):
        super(MyClass,self).__init__()
        self.__url = QUrl()

    def getUrl(self):
        return self.__url

    def setUrl(self,value):
        newUrl = QUrl(value)
        if (newUrl != self.__url):
            self.__url = newUrl
            self.urlChanged.emit()

    urlChanged = Signal()
    urla = Property(QUrl, getUrl, setUrl, notify = urlChanged)

class TestBug926 (unittest.TestCase):
    def testIt(self):
        app = QApplication([])
        qmlRegisterType(MyClass,'Example',1,0,'MyClass')
        view = QDeclarativeView()
        view.setSource(QUrl.fromLocalFile(adjust_filename('bug_926.qml', __file__)))
        self.assertEqual(len(view.errors()), 0)
        view.show()
        QTimer.singleShot(0, app.quit)
        app.exec_()

if __name__ == '__main__':
    unittest.main()
