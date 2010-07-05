'''Test cases for QDeclarativeView'''

import unittest

from PySide.QtCore import QUrl
from PySide.QtDeclarative import QDeclarativeView

from helper import adjust_filename, TimedQApplication


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

        self.app.exec_()

if __name__ == '__main__':
    unittest.main()
