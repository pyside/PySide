from PySide import QtCore, QtDeclarative

import unittest
from helper import adjust_filename, UsesQApplication


class TestBug(UsesQApplication):
    def testQMLFunctionCall(self):
        ownerData = QtDeclarative.QDeclarativePropertyMap()
        ownerData.insert('name', 'John Smith')
        ownerData.insert('phone', '555-5555')
        ownerData.insert('newValue', '')

        view = QtDeclarative.QDeclarativeView()
        ctxt = view.rootContext()
        ctxt.setContextProperty('owner', ownerData)
        view.setSource(QtCore.QUrl.fromLocalFile(adjust_filename('bug_997.qml', __file__)))
        view.show()
        QtCore.QTimer.singleShot(1000, self.app.quit)
        self.app.exec_()
        self.assertEqual(ownerData.value('newName'), ownerData.value('name'))

if __name__ == '__main__':
    unittest.main()
