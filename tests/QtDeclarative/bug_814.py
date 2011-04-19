#!/usr/bin/python
# -*- coding: utf-8 -*-

# Test case for PySide bug 814
# http://bugs.pyside.org/show_bug.cgi?id=814
# 2011-04-08 Thomas Perl <m@thp.io>
# Released under the same terms as PySide itself

from PySide.QtCore import QUrl, QAbstractListModel, QModelIndex
from PySide.QtDeclarative import QDeclarativeView

from helper import adjust_filename, TimedQApplication
import unittest

class ListModel(QAbstractListModel):
    def __init__(self):
        QAbstractListModel.__init__(self)
        self.setRoleNames({0: 'pysideModelData'})

    def rowCount(self, parent=QModelIndex()):
        return 3

    def data(self, index, role):
        if index.isValid() and role == 0:
            return 'blubb'
        return None

class TestBug814(TimedQApplication):
    def testAbstractItemModelTransferToQML(self):
        view = QDeclarativeView()
        view.setSource(QUrl.fromLocalFile(adjust_filename('bug_814.qml', __file__)))
        root = view.rootObject()
        model = ListModel()
        root.setProperty('model', model)
        view.show()

if __name__ == '__main__':
    unittest.main()

