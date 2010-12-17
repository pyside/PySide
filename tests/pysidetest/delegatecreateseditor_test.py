#!/usr/bin/python

import unittest
from helper import UsesQApplication

from testbinding import TestView
from PySide.QtCore import Qt
from PySide.QtGui import QAbstractItemDelegate, QComboBox

id_text = 'This is me'

class DelegateDoesntKeepReferenceToEditor(QAbstractItemDelegate):
    def createEditor(self, parent, option, index):
        comboBox = QComboBox(parent)
        comboBox.addItem(id_text)
        return comboBox


class DelegateKeepsReferenceToEditor(QAbstractItemDelegate):
    def __init__(self, parent=None):
        QAbstractItemDelegate.__init__(self, parent)
        self.comboBox = QComboBox()
        self.comboBox.addItem(id_text)

    def createEditor(self, parent, option, index):
        self.comboBox.setParent(parent)
        return self.comboBox


class EditorCreatedByDelegateTest(UsesQApplication):

    def testDelegateDoesntKeepReferenceToEditor(self):
        view = TestView(None)
        delegate = DelegateDoesntKeepReferenceToEditor()
        view.setItemDelegate(delegate)
        editor = view.getEditorWidgetFromItemDelegate()
        self.assertEqual(type(editor), QComboBox)
        self.assertEqual(editor.count(), 1)
        self.assertEqual(editor.itemData(0, Qt.DisplayRole), id_text)
        editor.metaObject()

    def testDelegateKeepsReferenceToEditor(self):
        view = TestView(None)
        delegate = DelegateKeepsReferenceToEditor()
        view.setItemDelegate(delegate)
        editor = view.getEditorWidgetFromItemDelegate()
        self.assertEqual(type(editor), QComboBox)
        self.assertEqual(editor.count(), 1)
        self.assertEqual(editor.itemData(0, Qt.DisplayRole), id_text)
        editor.metaObject()


if __name__ == '__main__':
    unittest.main()

