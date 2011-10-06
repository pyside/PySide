'''Test cases for QDeclarativeView'''

import unittest

from PySide.QtCore import QUrl, QObject, Property, Slot
from PySide.QtDeclarative import QDeclarativeView

from helper import adjust_filename, TimedQApplication

class MyObject(QObject):
    def __init__(self, text, parent=None):
        QObject.__init__(self, parent)
        self._text = text

    def getText(self):
        return self._text


    @Slot(str)
    def qmlText(self, text):
        self._qmlText = text

    title = Property(str, getText)


class TestQDeclarativeView(TimedQApplication):

    def testQDeclarativeViewList(self):
        view = QDeclarativeView()

        dataList = ["Item 1", "Item 2", "Item 3", "Item 4"]

        ctxt = view.rootContext()
        ctxt.setContextProperty("myModel", dataList)

        url = QUrl.fromLocalFile(adjust_filename('view.qml', __file__))
        view.setSource(url)
        view.show()

        self.assertEqual(view.status(), QDeclarativeView.Ready)


    def testModelExport(self):
        view = QDeclarativeView()
        dataList = [MyObject("Item 1"), MyObject("Item 2"), MyObject("Item 3"), MyObject("Item 4")]

        ctxt = view.rootContext()
        ctxt.setContextProperty("myModel", dataList)

        url = QUrl.fromLocalFile(adjust_filename('viewmodel.qml', __file__))
        view.setSource(url)
        view.show()

        self.assertEqual(view.status(), QDeclarativeView.Ready)


if __name__ == '__main__':
    unittest.main()
