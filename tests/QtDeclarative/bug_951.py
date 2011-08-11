from PySide.QtDeclarative import QDeclarativeItem, qmlRegisterType, QDeclarativeView
from PySide.QtCore import QUrl

from helper import adjust_filename, TimedQApplication
import unittest

class MyItem(QDeclarativeItem):
    COMPONENT_COMPLETE_CALLED = False
    def __init__(self,parent=None):
        super(MyItem, self).__init__(parent)
        self.setObjectName("myitem")

    def componentComplete(self):
        MyItem.COMPONENT_COMPLETE_CALLED = True
        super(MyItem, self).componentComplete()

class TestRegisterQMLType(TimedQApplication):
    def setup(self):
        TimedQApplication.setup(self, 100 * 3) # 3s

    def testSignalEmission(self):
        qmlRegisterType(MyItem, "my.item", 1, 0, "MyItem")

        view = QDeclarativeView()
        view.setSource(QUrl.fromLocalFile(adjust_filename('bug_951.qml', __file__)))

        self.app.exec_()
        self.assertTrue(MyItem.COMPONENT_COMPLETE_CALLED)

if __name__ == '__main__':
    unittest.main()
